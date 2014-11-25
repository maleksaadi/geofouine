using System;
using System.IO;


////////////////////////////////////////
//
// This Class does "low-level" IO with
// the GPS. It's very basic.
//
class GPS
 {
  static private readonly char[] zero={'0'};
  private System.IO.Ports.SerialPort gpsDevice;

  //////////////////////////////////////
  static public string AsSeconds(string raw)
   {
    Double this_float=0;
    Double.TryParse("0."+raw,out this_float);
    return (this_float*60).ToString("00.000");
   }

  //////////////////////////////////////
  static public string Reformat(string raw)
   {
    int length= (raw[0]!='0') ? 2:3; 
    return 
     raw.Substring(0,length).TrimStart(zero)
     +"⁰"
     +raw.Substring(length,2)
     +"'"
     +AsSeconds(raw.Substring(length+3)) // skips '.'
     +"\"";
   }

  //////////////////////////////////////
  public string[] GetPosition()
   {
    string[] splitString;
    do
     {
      //string this_line=gpsDevice.ReadLine();

      splitString=(gpsDevice.ReadLine()).Split(new Char[]{','});
     }
    while ( (splitString[0]!="$GPRMC") || 
            (splitString[2]!="A") );

    return new string[] 
     {
      splitString[3].TrimStart(zero),
      splitString[4],
      splitString[5].TrimStart(zero),
      splitString[6]
     };
   }

  //////////////////////////////////////
  public GPS(string gpsDeviceName)
   {
    try 
     {
      // open device in 4800, 8,n,1, and...
      gpsDevice=
       new System.IO.Ports.SerialPort(gpsDeviceName,
                                      4800,
                                      System.IO.Ports.Parity.None,
                                      8,
                                      System.IO.Ports.StopBits.One);

      // ...set full handshake protocol
      gpsDevice.Handshake=System.IO.Ports.Handshake.RequestToSendXOnXOff;

      gpsDevice.Open();
     }
    catch
     {
      // oh noes!!1!
      System.Console.WriteLine("ach! grosse malheur!");
     }
   }
 }

class WarDrive
 {
  // linux version
  const string gpsDeviceName=@"/dev/ttyUSB0";

  public static void Main()
   {
    // create a GPS file stream thingie
    //
    GPS gps=new GPS(gpsDeviceName);
    while (true)
     {
      //System.Console.WriteLine(gps.GetPosition());
      string[] machin=gps.GetPosition();
      foreach(string s in machin)
       System.Console.Write("{0} ",s);
      
      System.Console.WriteLine("\t{0} {1} {2} {3}",
                               GPS.Reformat(machin[0]),
                               machin[1],
                               GPS.Reformat(machin[2]),
                               machin[3]);
     }
   }
 }
