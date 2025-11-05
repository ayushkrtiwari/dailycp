# set -e

# # compile executable
# g++ -std=c++17 -O2 largeinout/code.cpp -Wl,-subsystem,console -o code.exe

# # Multiple times generate same output
# # useful for making dummy datasets with repeated data 
# echo "Started Code input output"
# while true; do
#     for i in {1..5}; do
#         ./code.exe < input.txt >> repeated_output.txt
#     done
#     # sleep a bit so the loop is not a busy spin (optional)
#     sleep 0.1
# done

# # want to get new file repeated text
# # for i in {1..10}; do
# #     cat output.txt >> final.txt
# # done

# ____________________________________________________________________

# output just once, simple input to output

#!/usr/bin/env bash
set -e
g++ -std=c++17 -O2 largeinout/code.cpp -o code.exe
echo "Running once..."
./code.exe < largeinout/input.txt > largeinout/output.txt
echo "Done. Output written to largeinout/output.txt"

# _____________________________________________________________________

# #!/usr/bin/env bash
# set -e

# # compile executable
# g++ -std=c++17 -O2 largeinout/code.cpp -Wl,-subsystem,console -o code.exe

# # Multiple times generate same
# echo "Started Code input output"
# while true; do
#     ./code.exe < largeinout/input.txt > largeinout/output.txt
#     # sleep a bit so the loop is not a busy spin (optional)
#     sleep 0.1
# done