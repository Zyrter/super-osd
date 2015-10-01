# Introduction #

Keeping an accurate time is important for datalogging. Without timing information, each data point can only be stored sequentially. V3 Lite and V3 Pro have an RTC oscillator (32.768 kHz), but the time must be set on each restart as there is no battery backup.

# Solutions #

As there is a GPS connection, the GPS data can be used to provide accurate UTC time to within 1 second under normal conditions. While GPS is accurate to as few as 40 nanoseconds, latency over the comms port and internal processing will reduce this to a few hundred milliseconds at best.

GPS provides uncorrected UTC time (that is, UTC without leap seconds.) UTC corrections are often, but not always added by the GPS receiver; the information is stored in the almanac. Therefore, the time may be off by as much 13 seconds, but this offset will be consistent.