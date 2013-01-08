#!/usr/bin/ruby

require "rubygems"
require 'bundler'
require "serialport"
require 'eventmachine'
require 'json'
require 'pp'
require "rest_client"

#params for serial port
port_str = "/dev/ttyUSB0"
baud_rate = 57600
data_bits = 8
stop_bits = 1
parity = SerialPort::NONE
API_KEY = 'fe849ccf68400b34187e9fca856a3387'

# rest client setup

def send_data json
  params = {}
  params['apikey'] = API_KEY
  params['json'] = json
  
	begin
  	@response = RestClient.get 'http://emoncms.org/api/post', {:params => params, :user_agent => "Serial Gateway" }
		@return_code = @response.code
	rescue RestClient::Exception => e
		@response = "{}"
		@return_code = e.http_code
	rescue Exception => e
	  puts "An exception occured #{e.message}"
	end
  
end

EventMachine::run do

  EventMachine.add_periodic_timer(60) do
    json = '{"Heartbeat": 1}'
    send_data(json)
    puts "Sending Heartbeat"
  end

  EventMachine::defer do
    loop do
      puts "Start main Loop"
      sp = SerialPort.new(port_str, baud_rate, data_bits, stop_bits, parity)
      line = sp.gets
      print "We got #{line}"
      
      begin
        sensor_data = JSON.parse line
      rescue
        puts " garbage data...skipping"
      end
      
      if !sensor_data.nil?
        print " ==> "
        pp sensor_data
        send_data(line)
      end
      puts "End main loop"
      sp.close
    end
  end
end

