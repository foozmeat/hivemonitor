#!/usr/bin/env ruby

require "rubygems"
require 'bundler/setup'
Bundler.require

require 'json'
require 'pp'
require 'logger'

$log = Logger.new(STDOUT)
$log.level = Logger::DEBUG

#params for serial port
#port_str = "/dev/ttyUSB0"
port_str = "/dev/tty.usbserial-A900XSF2"

if (!File.exist?(port_str))
  raise "Port #{port_str} doesn't exist"
end

baud_rate = 57600
data_bits = 8
stop_bits = 1
parity = SerialPort::NONE
EMON_API_KEY = 'xxx'
SENSE_API_KEY = 'xxx'

$sense_ids = {
  "DS18B20" => 24203,
  "DHT22T" => 24337,
  "DHT22H" => 24338
}

sp = SerialPort.new(port_str, baud_rate, data_bits, stop_bits, parity)

# rest client setup

def send_data_to_emon json
  params = {}
  params['apikey'] = EMON_API_KEY
  params['json'] = json
  
	begin
  	@response = RestClient.get 'http://emoncms.org/api/post', {:params => params, :user_agent => "Serial Gateway" }
		@return_code = @response.code
	rescue RestClient::Exception => e
		@response = "{}"
		@return_code = e.http_code
	rescue Exception => e
	  $log.error("An exception occured sending to Emon: #{e.message}")
	end
  
end

def send_data_to_sense data
  params = {}

  data.each do |key, value|
    json = "{ \"feed_id\": #{$sense_ids[key]}, \"value\": #{value} }"
    $log.debug("Sending " + json)

    begin
      @response = RestClient.post 'http://api.sen.se/events/?sense_key=' + SENSE_API_KEY, json, :content_type => "application/json", :user_agent => "Serial Gateway"
      @return_code = @response.code
      $log.debug(@response.body)
    rescue Exception => e
      $log.error("An exception occured sending to Sen.se: #{e.message}")
    end

  end


end

EventMachine::run do

  EventMachine.add_periodic_timer(60) do
    json = '{"Heartbeat": 1}'
    send_data_to_emon(json)
    $log.info { "Sending Heartbeat" }
  end

  EventMachine::defer do
    loop do
      line = sp.gets.chomp
      if line[0,3] == "###"
        # We got a comment from the Arduino; just print it
        $log.info { line }
      elsif line[0] == "{"
        # We probably got some JSON so try and parse it
        begin
          sensor_data = JSON.parse line
        rescue
          $log.error { "garbage data...skipping" }
        end
      
        if !sensor_data.nil?
          $log.info(sensor_data.to_s)
          send_data_to_emon(line)
          send_data_to_sense(sensor_data)
        end
      end
    end
  end
end

sp.close
