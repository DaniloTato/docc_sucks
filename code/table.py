import subprocess
import pandas as pd
import numpy as np

# Config
executable = "./code/build/tsp"
input_file = "code/tests/dsj1000.tsp"
Ns = [10, 50, 100, 200, 400, 600, 800, 1000]
algos = ["NN", "CL", "MST"]
num_seeds = 10
results = []

for N in Ns:
    for seed_idx in range(num_seeds):
        print(f"Running N={N}, seed run {seed_idx+1}...")
        proc = subprocess.run([executable, str(N)], input=open(input_file, "rb").read(),
                              stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        output = proc.stdout.decode()
        for line in output.splitlines():
            # Expected format: ALGO=NN N=500 SEED=123 COST=19431973 TIME_in_micro_s=293 TOUR_LEN=500
            fields = {}
            for part in line.split():
                k,v = part.split("=")
                fields[k] = v
            results.append({
                "N": int(fields["N"]),
                "ALGO": fields["ALGO"],
                "COST": int(fields["COST"]),
                "TIME_in_micro_s": int(fields.get("TIME_in_micro_s", fields.get("TIME_ms", 0)))
            })

df = pd.DataFrame(results)

summary = df.groupby(["N","ALGO"]).agg(["mean","std"])[["COST","TIME_in_micro_s"]]
print(summary)

summary.to_csv("tsp_results_summary.csv")