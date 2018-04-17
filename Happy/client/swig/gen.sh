#!/usr/bin/env bash
#rm *.cs
swig -c++ -csharp -outdir "cs" -o "../src/network_wrap.cxx" network.i