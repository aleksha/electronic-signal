# electronic-signal

Create signals for TPC-based scattering experiments 

This project contains a tool to create a spectrum of the electronic signal for the 
Flash ADC used with TPC (ACTAF's parameters are used as a default). 
The code is tested with CERN ROOT v6.22. Run it using command:
```bash
root -b Run.C+
```

To watch figures on a remote machine I use simple Python3 web-server
```bash
python3 -m http.server 8000
```

## Dependencies

  * [CERN ROOT](https://root.cern.ch/)

## How it works
 0. Define TPC, readout and generator configurations in `Parameters.h`
 1. Create a map of induced charge on rings with **step_size** width.
  Electron is mowing perpendicular to anode at **r=0**.

