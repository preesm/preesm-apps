from tqdm import tqdm
import subprocess
import os
import pandas as pd
import datetime
import pathlib
pathlib.Path("Log").mkdir(parents=True, exist_ok=True)
Number_of_executions = 1

file_list = [f for f in os.listdir("./") if f[-4:]==".266"]
thread_list = [1, 2, 3, 4, 6, 12]

data = []

thread_bar = tqdm(desc="Thread", position=1)
for bitstream in tqdm(file_list, desc="Bitstream", position=0):
	thread_bar.reset(total=len(thread_list))
	for thread in thread_list:
		process_input = ["multitime", "-n", str(Number_of_executions), "./dectest", "-i", bitstream, "-t", "1", "-e", str(thread), "-o", """dev\null"""]
		process = subprocess.Popen(process_input, stdout=subprocess.PIPE, stderr = subprocess.STDOUT)
		output = process.communicate()[0]
		try:
			output = str(output).strip().split()
			output = output[output.index("Median")+2:][:5]
			data.append([bitstream, thread]+output)
		except:
			data.append([bitstream, thread]+[-1]*5)
		thread_bar.update()
df = pd.DataFrame(data=data, columns=["Bitstream", "Thread", "Mean", "Std.Dev.", "Min", "Median", "Max"])
df.to_csv("output_"+str(datetime.datetime.now())[:-7].replace(" ", "_").replace('-', "").replace(":", "")+".csv")
