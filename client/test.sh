#!/bin/bash

declare -a COLORS=("RED" "GREEN" "BLUE")
declare -a STATES=("ON" "OFF")
declare -a RATES=(0 1 2 3 4 5)


function print_usage {
  echo "Usage: $0 server_id_pipe" >&2
  exit 1
}

function print_error {
  echo $1 1>&2;
  exit 1;
}

if [ "$#" -lt 1 ]; then
  print_usage
fi

TO_SERVER=$1

COLOR_RESULT="COLOR_NONE"

function color_test {
  for color in "${COLORS[@]}"
  do
    COLOR_RESULT=`./client.sh $TO_SERVER  --set color $color`
    if [[ ! $? -eq 0 ]]; then print_error "error on --set color"; fi
    if [[ ! -z $COLOR_RESULT ]]; then print_error "non-empty reply from --set-color: $COLOR_RESULT"; fi
    COLOR_RESULT=`./client.sh $TO_SERVER  --get color`
    if [[ ! $? -eq 0 ]]; then print_error "error on --get color"; fi
    if [[ -z $COLOR_RESULT ]]; then print_error "empty reply from --get-color"; fi
    if [[ ! $COLOR_RESULT -eq "$color" ]]; then print_error "invaid reply from --get-color: $COLOR_RESULT"; fi
  done
}

STATE_RESULT="STATE_NONE"

function state_test {
  for state in "${STATES[@]}"
  do
    STATE_RESULT=`./client.sh $TO_SERVER  --set state $state`
    if [[ ! $? -eq 0 ]]; then print_error "error on --set state"; fi
    if [[ ! -z $STATE_RESULT ]]; then print_error "non-empty reply from --set-state: $STATE_RESULT"; fi
    STATE_RESULT=`./client.sh $TO_SERVER  --get state`
    if [[ ! $? -eq 0 ]]; then print_error "error on --get state"; fi
    if [[ -z $STATE_RESULT ]]; then print_error "empty reply from --get-state"; fi
    if [[ ! $STATE_RESULT -eq "$state" ]]; then print_error "invaid reply from --get-state: $STATE_RESULT"; fi
  done
}

RATE_RESULT="RATE_NONE"

function rate_test {
  for rate in "${RATES[@]}"
  do
    RATE_RESULT=`./client.sh $TO_SERVER  --set rate $rate`
    if [[ ! $? -eq 0 ]]; then print_error "error on --set rate"; fi
    if [[ ! -z $RATE_RESULT ]]; then print_error "non-empty reply from --set-rate: $RATE_RESULT"; fi
    RATE_RESULT=`./client.sh $TO_SERVER  --get rate`
    if [[ ! $? -eq 0 ]]; then print_error "error on --get rate"; fi
    if [[ -z $RATE_RESULT ]]; then print_error "empty reply from --get-rate"; fi
    if [[ ! $RATE_RESULT -eq "$rate" ]]; then print_error "invaid reply from --get-rate: $RATE_RESULT"; fi
  done
}

while true
do
  color_test
  rate_test
  state_test
done


# while true 
# do
# color_test; sleep 0.1;
# done &

# while true 
# do
# state_test; sleep 0.1;
# done &

# while true 
# do
# rate_test; sleep 0.1;
# done &

# wait


