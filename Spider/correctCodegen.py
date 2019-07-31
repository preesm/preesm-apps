#!/usr/bin/python3

import re
import sys

if len(sys.argv) < 2:
    print("Wrong number of arguments. Expected 2. {}".format(sys.argv[0]))
    exit(0)

toModif =   [
                [
                    ["bo_Update_Actor", "bo_Update_Actor", "actor_weights_size"], 
                    ["if_weights_actor", "if_weights_actor_out"]
                ],
                [
                    ["bo_Update_Actor", "bo_Update_Actor", "actor_bias_size"], 
                    ["if_bias_actor", "if_bias_actor_out"]
                ],
                [
                    ["bo_Update_Critic", "bo_BroadcastCriticWeights", "critic_weights_size"], 
                    ["if_weights_critic", "if_weights_critic_out"]
                ],
                [
                    ["bo_Update_Critic", "bo_BroadcastCriticBias", "critic_bias_size"], 
                    ["if_bias_critic", "if_bias_critic_out"]
                ],
                [
                    ["bo_BroadcastNextStateFeature", "bo_BroadcastStateFeature"], 
                    ["bo_Init_State", "bo_End_State"]
                ]
            ]



readFile = open(sys.argv[1], "r")
s = readFile.read()


regEdges = re.compile(r"{[^}]+__[^}]+}")
print(regEdges.findall(s))
s = regEdges.sub("", s)
print("Removed unwanted edges...")


for val in toModif:
    search = val[0]
    modif = val[1]

    strReg = r"{[^}]+"
    for i in search:
        strReg += i + "[^}]+"
    strReg += r"[^}]+}"

    regNullptr = re.compile(strReg)
    patterns = regNullptr.findall(s)
    print(patterns)

    if(len(patterns) == 1):
        replace = re.sub("nullptr", modif[0] , patterns[0], 1)
        replace = re.sub("nullptr", modif[1] , replace, 1)
        print(replace)
        s = regNullptr.sub(replace, s)
    
print("Modifed delay edges...")

readFile.close()



writeFile = open(sys.argv[1], 'w')
writeFile.write(s)
writeFile.close()


