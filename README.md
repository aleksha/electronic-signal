# electronic-signal

Create signals for TPC-based scattering experiments

This project contains a tool to create a spectrum of the electronic signal for the
Flash ADC used with TPC (ACTAF's parameters are used as a default).
The code is tested with CERN ROOT v6.22. Run it using command:
```bash
root -b Run.C+
```

It also saves a map into **CHARGE_MapR.txt**.

To watch figures on a remote machine I use simple Python3 web-server
```bash
python3 -m http.server 8000
```

**Important:** so far the calculation for electrons, which are close-to-anode
(**low h**) are wrong, due to granularity problem. This problem can be
walk-around with **step_size=0.01 mm**. Small irregularity still exists!
It's visible on a current graph, but it's small wrt. to all current values.


## Dependencies

  * [CERN ROOT](https://root.cern.ch/)


## How it works

  1. Define TPC, readout and generator configurations in `Parameters.h`

  2. Define pad numbering function `get_pad_number()`

  3. Create a map of induced charge on rings with **step_size** width.
    Electron is mowing perpendicular to anode at **r=0**.

  4. Calculate induced charge and current with defined anode
    structure for an electron in point **(x,y)** using an overlap
    of the map and anodes.

  5. Find which of anode is fired, using the largest integral of current.

  6. Rescale currents for each of anodes with a common factor, which
    is evaluated to set the current integral for the fired anode to unity.
