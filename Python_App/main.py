import json
from cs50 import SQL
from time import localtime, sleep
from boltiot import Bolt

db = SQL("sqlite:///maindb.db")

api_key = "9c8c9edd-132b-4d96-a92b-0089580ebd1a"
device_id = "BOLT7420916"
uname = input("Enter DORMIR username: ")

bolt_inst = Bolt(api_key, device_id)

def main():
    alarm_on = False
    ring = False
    bolt_inst.serialBegin('9600')
    
    while True:
        try:
            read_resp = bolt_inst.serialRead('10')
            read_data = json.loads(read_resp)            

            check_in = db.execute("SELECT in-hour FROM records WHERE date=CURRENT_DATE")

            if not check_in:
                if read_data['value'] == 'start\n':
                    db.execute("INSERT INTO records(date, in-hour, in-min) VALUES(current_date, :hour, :mins)", hour=localtime().tm_hour, mins=localtime().tm_min)
                    alarm_on = True

            else:
                wakeup_time = db.execute("SELECT wtime FROM users WHERE username=:username",username=uname)[0]['wtime']

                if localtime().tm_hour >= wakeup_time and alarm_on:
                    if not ring:
                        bolt_inst.serialWrite('ring')
                        ring = True

                if ring and read_data['value'] == 'stop\n':
                    rc = db.execute("SELECT COUNT(*) FROM records")[0]['COUNT(*)']
                    db.execute("UPDATE records SET out-hour=:ohr AND out-min=:omin WHERE id=:id", ohr=localtime().tm_hour, omin=localtime().tm_min, id=rc)
                    ring = False
                    alarm_on = False
            
            sleep(15)
            
            
        except Exception as e:
            print("Error: ",e)
            sleep(15)

            

if __name__ == '__main__':
    main()
