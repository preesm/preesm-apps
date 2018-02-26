#!/bin/bash
# desc : This script before lunch 
# Executez la dans le dossier des scripts

sudo bash configure.sh;
rm -r Save_stats;
rm -r stats;
mkdir Save_stats;
mkdir stats;

sudo bash script_stress_conso.sh A15 4 OFF;
mv ./stats "./Save_stats/stats_A15_OFF_4";
mkdir stats;


sudo bash script_stress_conso.sh A7 4 OFF;
mv ./stats "./Save_stats/stats_A7_OFF_4";
mkdir stats;


