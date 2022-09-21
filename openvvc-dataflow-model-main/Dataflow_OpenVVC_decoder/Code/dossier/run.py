from tqdm import tqdm
import subprocess
import os
import pandas as pd
import datetime

Number_of_executions = 20

file_list = [f for f in os.listdir("./") if f[-4:]==".266"]
# file_list = ["ArenaOfValor_1920x1080_60_8_420_-q_22.266"]
data = []
thread = 1

for bitstream in tqdm(file_list, desc="Bitstream", position=0):
	f = open("input.txt", 'w')
	f.write(str(bitstream)+" ")
	f.close()
	process_input = ["multitime", "-n", str(Number_of_executions), "./DECVVC"]
	process = subprocess.Popen(process_input, stdout=subprocess.PIPE, stderr = subprocess.STDOUT)
	output = process.communicate()[0]
	try:
		output = str(output).strip().split()
		output = output[output.index("Median")+2:][:5]
		data.append([bitstream, thread]+output)
	except:
		data.append([bitstream, thread]+[-1]*5)

df = pd.DataFrame(data=data, columns=["Bitstream", "Thread", "Mean", "Std.Dev.", "Min", "Median", "Max"])
df.to_csv("Preesm_output_"+str(datetime.datetime.now())[:-7].replace(" ", "_").replace('-', "").replace(":", "")+".csv")
