import json
from cs50 import SQL
from time import localtime, sleep
from boltiot import Bolt

db = SQL("sqlite:///maindb.db")

api_key = "Your BOLT API key"
device_id = "Your BOLT device ID"

bolt_inst = Bolt(api_key, device_id)

def main():
    alarm_on = False
    ring = False
    bolt_inst.serialBegin('9600')
    
    while True:
        try:
            read_resp = bolt_inst.serialRead('10')
            read_data = json.loads(read_resp)
            
            if read_data['value'] == 'start\n':
                print(localtime().tm_hour)
                alarm_on = True
                
            if localtime().tm_hour == 8 and alarm_on:
                if not ring:
                    bolt_inst.serialWrite('ring')
                    ring = True

            if ring and read_data['value'] == 'stop\n':
                print(localtime().tm_hour)
                ring = False
                alarm_on = False
            
            sleep(15)
            
            
        except Exception as e:
            print("Error: ",e)
            sleep(15)

            

if __name__ == '__main__':
    main()
