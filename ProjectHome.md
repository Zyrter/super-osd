Super OSD is an on screen display intended primarily for model aircraft with FPV systems. It is an open hardware project. The firmware and the hardware are both open source.

In brief, an on screen display embeds telemetry information onto a video signal. Super OSD is intended to be used with FPV systems, and can display many types of data on a video signal. It works with both PAL and NTSC video signals.

Originally, two projects were planned: a Lite version and a Pro version. The Lite version is approaching the point of being production ready. However the Pro version has been put on hold for now, and will only be released later.

<a href='http://www.youtube.com/watch?feature=player_embedded&v=AIJ37kDix5w' target='_blank'><img src='http://img.youtube.com/vi/AIJ37kDix5w/0.jpg' width='425' height=344 /></a>

An overview:
  * Two processor solution; one dsPIC33F for OSD, one dsPIC33F for background tasks.
  * Uses a dsPIC33FJ128GP804 MCU/DSP to embed crisp black and white graphics (outlined) onto a PAL/NTSC video signal.
  * A full graphics library written for the OSD, supporting high speed graphics manipulation. Optimised horizontal/vertical lines, arbitrary lines, text, circles, rectangles, fills and test routines built in.
  * 240x208 pixel resolution (sufficient for advanced graphics, including an artificial horizon, ticker-tape altimeter/airspeed...)
  * Small size: 50mm x 39mm. (75mm x 39mm with connectors.)
  * Light weight (<20 grams.)
  * Integrated 3.3V @ 600mA (~2W) switching power supply (4.5V - 30V input) for OSD and accessories. (450mA available for accessories.)
  * 2MB/4MB integrated Flash storage for datalogging and settings.
  * Can provide all basic flight data with just a GPS device.
  * Additional support for 9DOF acc/gyro/mag board, current sensors, motor RPM, horizon sensors, and more.

Most of all - this project is intended to be low cost - so will sell for around US $90. Hacking is permitted - actually, encouraged - so there are programming connectors on the board to allow for software tweaks to be made.