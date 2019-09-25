import sqlite3
import time
from Sensores import sensor_temperatura
from Sensores import i2c
from sqlite3 import Error



def sql_connection():
    try:
        conn = sqlite3.connect('Sonda_LSD.db')
        return conn
    except Error:
        print(Error)
        
def sql_table(conn):
    cur =conn.cursor()
    cur.execute("CREATE TABLE lecturas(N integer PRIMARY KEY AUTOINCREMENT, datatime integer, Tempertatura integer,pH integer,DO integer,CE integer,TDS integer, S integer)")
    conn.commit()

def sql_insert(conn,lecturas):
    cur=conn.cursor()
    cur.execute("INSERT INTO lecturas(datatime,Tempertatura,pH,DO,CE,TDS,S) VALUES(datetime('now','localtime'),?,?,?,?,?,?)",lecturas)
    conn.commit()
    
conn= sql_connection()
sql_table(conn)


c = conn.cursor()
##Lectura de Sensores
while True:
    temp=sensor_temperatura.read_temp()[0]
    reading_time = time.ctime(time.time())
    DO= i2c.leerSensores("R","DO")
    PH= i2c.leerSensores("R","PH")
    CEt= i2c.leerSensores("R","CE")
    #
    CE= CEt[0:4]
    TDS= CEt[5]
    S= CEt[7:11]
    
    SEN= {"Temp":temp,"DO":DO,"OPR":98,"PH":PH, "CE":CE,"TDS": TDS, "S": S}
    print (SEN)
    lect=(temp,DO,PH,CE,TDS,S)
   ## print (temp)
   ## aux=(temp,temp,temp,temp,temp)
    ##print (reading_time)
    ##print ("CE: "+ str(CE[0:4]))
    ##print ("TDS: "+ str(CE[5]))
    ##print ("S: "+ str(CE[7:11]))



    ## Almacenamiento en BD

  ##  c.execute("INSERT INTO lecturas VALUES ( 1,datetime('now','localtime'), temp, PH, CE, TDS,S)")



#    c.execute('''INSERT INTO lecturasPy(datatime,Tempertatura,pH,CE,TDS,S) VALUES(datetime('now','localtime'),?,?,?,?,?)''', aux)
  #  conn.commit()
    sql_insert(conn,lect)
    time.sleep(2.0)

