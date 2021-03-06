#!/usr/bin/env ruby

require "rubygems"
require 'bundler/setup'
Bundler.require

require 'json'
require 'pp'
require 'logger'
require 'date'

$log = Logger.new(STDOUT)
# $log = Logger.new('gateway.log', 'daily')
$log.level = Logger::INFO

#params for serial port
#port_str = "/dev/ttyUSB0"
#port_str = "/dev/tty.usbserial-A900XSF2"
port_str = "/dev/tty.usbserial-A1017IRP"

if (!File.exist?(port_str))
  raise "Port #{port_str} doesn't exist"
end

baud_rate = 57600
data_bits = 8
stop_bits = 1
parity = SerialPort::NONE
EMON_API_KEY = ''
SENSE_API_KEY = ''
STATHAT_API_KEY = ''

$sense_ids = {
  "DS18B20" => 24203,
  "DHT22T" => 24337,
  "DHT22H" => 24338
}

nilLineCount = 0;

$sp = SerialPort.new(port_str, baud_rate, data_bits, stop_bits, parity)

# rest client setup

def send_data_to_emon json
	return unless EMON_API_KEY != ""
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
  else
    $log.debug("Logged data to EmonCMS")
	end
  
end

def send_data_to_sense data
	return unless SENSE_API_KEY != ""
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

def send_data_to_stathat data
  return unless STATHAT_API_KEY != ""
  params = {}

  data.each do |key, value|
    begin
      # The Bee counter should use a count instead of a value
      if key.match("BC").nil?
        StatHat::API.ez_post_value(key, "a0kyl7F9F2vIXEO8", value)
      else
        StatHat::API.ez_post_count(key, "a0kyl7F9F2vIXEO8", value)
      end        
    rescue Exception => e
      $log.error("An exception occured sending to stathat: #{e.message}")
    else
      $log.debug("Logged data to Stathat")
    end
  end
	
end

def log_to_sqlite data

  date = DateTime.now().strftime("%Y-%m")
  dbname = "#{date}-#{DATABASE_NAME}"

  SQLite3::Database.new dbname
  db = SQLite3::Database.open dbname
  now = DateTime.now.to_s

  begin
    db.execute "CREATE TABLE IF NOT EXISTS hive_data (date TEXT NOT NULL, data_key TEXT NOT NULL,data_value REAL NOT NULL);"
  rescue SQLite3::Exception => e 
      puts "Exception occured"
      puts e
  end
  
  data.each do |key, value|
    db.execute "INSERT INTO hive_data (date,data_key,data_value) VALUES ('#{now}','#{key}', '#{value}')"
    # $log.debug("Logged data to sqlite")
  end  
  
  db.close if db
  
end

def reset_port
  $sp.close
  $sp = SerialPort.new(port_str, baud_rate, data_bits, stop_bits, parity)
end

EventMachine::run do

  EventMachine.add_periodic_timer(60) do
    json = '{"Heartbeat": 1}'
    send_data_to_emon(json)
    $log.info { "Sending Heartbeat" }
  end

  EventMachine::defer do
    loop do

      line = $sp.gets
      if line.nil?
        $log.error("Incoming data is nil")
        nilLineCount += 1
        
        if nilLineCount >= 5
          reset_port
          nilLineCount = 0
          $log.error("Port reset because of nil data")
        end
        
        next
      end
      line.chomp!
      $log.debug("Incoming data: " + line)
      
      # next if line.nil?
      # line = line.chomp
      
      if line[0,3] == "###"
        # We got a comment from the Arduino; just print it
        $log.info { line }
      else
        # We probably got some JSON so try and parse it
        begin
          sensor_data = JSON.parse line
        rescue
          $log.error { "garbage data: #{line}" }
        end
      
        if !sensor_data.nil?
          $log.info(sensor_data.to_s)
          send_data_to_emon(line)
          # send_data_to_sense(sensor_data)
          send_data_to_stathat(sensor_data)
          log_to_sqlite(sensor_data)
        else
          $log.error("Sensor data was nil!")
        end
      end
    end
  end
end

$sp.close
