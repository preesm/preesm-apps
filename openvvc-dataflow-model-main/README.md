# OpenVVC dataflow model
An open-source VVC decoder developped based on dataflow modeling and the OpenVVC decoder.  


## Installation  
1) Install PREESM version 3.20.0 https://preesm.github.io/get/  
2) Dowenload OpenVVC project commit 34a8aa7  via the link: https://github.com/OpenVVC/OpenVVC 
3) open the rebuild.sh file and specify the path of the openVVC project and the OpenVVC dataflow model project 
4) run the rebuild.sh file: 
```bash
.\rebuild.sh
```
## Changelog

Support Tile parallelism.

## Using the Dataflow model
- set the value of the tile_number parameter according to the number of used tile contained in the bitstream to be decoded.  
### Run the workflow
```bash
In the Project explorer of Preesm, right-click on the Codegen.workflow file in the “Workflows” directory
Click “Preesm > Run Workflow”
Choose the TestComPC.scenario file in the “Scenarios” directory
A Gantt chart is displayed and you can find the code that has been generated in “/Code/generated”.
```
### Some manual changements:
* In the generated folder make the following changes for evrey corex.c file  
1. change the loop ending condition from !PreesmStopThread by PreesmStopThread    
2. add inside the loop PreesmStopThread=PreesmStopThread-1;  
3. remove the attach function from inside the loop and put it just before the start of the loop    
4. remove the detach function from inside the loop and put it just after the finishing of the loop 
* in the generated folder in the main.c file set the value of PreesmStopThread equal to N with N is the number of iteration needed to be performed to decode a sequence. The value of N is different for each sequence as showing in the table below:     

| Sequence | PreesmStopThread |   
| :------: | :--: |   
| Campfire | 191 |      
| DaylightRoad2 | 191 |   
| CatRobot1 | 191 |    
| FoodMarket4 | 191 |    
| ParkRunning3 | 191 |    
| Tango2 | 186 |   
| BQTerrace | 376 |   
| Cactus | 253 |   
| MarketPlace| 376 |     
### Building the project  
```bash
mkdir bin  
cd bin  
mkdir make  
cd make  
cmake ../.. && make  
cd Debug 
``` 

## License
For open source projects, say how it is licensed.

