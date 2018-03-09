#!/bin/bash
mv *-F.Cu* i2cMaster.GTL
mv *-B.Cu* i2cMaster.GBL
mv *-F.SilkS* i2cMaster.GTO
mv *-B.SilkS* i2cMaster.GBO
mv *-F.Mask* i2cMaster.GTS
mv *-B.Mask* i2cMaster.GBS
mv *-Edge* i2cMaster.GKO
mv *.drl i2cMaster.TXT