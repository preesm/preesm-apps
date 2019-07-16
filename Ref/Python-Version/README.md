Python's reference code for CACLA algorithm
===

To run it properly without affecting your system, use a virtual environment.

Installation:
--

**WARNING:** You will need python3.5 or higher to run the program.

1. sudo pip install virtualenv
2. virtualenv -p python3.5 ./virtual
3. source virtual/bin/activate *This line should be executed every time you'll need to use the script. It sets you in the virtual environment.*
4. pip install -r requirements.txt

 
Run:
--

Now that you have prepare the libraries, you can perform training.

1. source virtual/bin/activate
2. python3 main.py train *-environment [environment]* -[optional options]

As for now, some of the stop conditions are based on the reward given by the **Pendulum-v0** environment. Feel free to change theese in the *run* method in *cacla.py* file.
