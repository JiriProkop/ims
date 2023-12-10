import subprocess

for i in range(5, 100):
    print("\nskacelova green time: " + str(i) + "\npyrkynova green time: " + str(i - 4), flush=True)
    simulation = subprocess.run(["./crossroad", "1000", str(i), str(i - 4)])
        