import subprocess

def run_executable(executable_path, command_args, num_runs):
    for _ in range(num_runs):
        try:
            subprocess.run(["python3"] + ["main.py"], check=True)
            subprocess.run([executable_path] + command_args, check=True)
        except subprocess.CalledProcessError as e:
            print(f"Error running {executable_path}: {e}")
            break
        else:
            print(f"{executable_path} executed successfully.")

if __name__ == "__main__":
    # Replace these values with your executable and command-line arguments
    executable_path = "bin/RectPackerTest"
    command_args = ["output_images", "0"]  # Modify with your desired arguments
    num_runs = 1  # Change the number of times you want to run the executable

    run_executable(executable_path, command_args, num_runs)
