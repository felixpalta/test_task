#!/bin/bash

function print_usage {
  echo "Usage: $0 [pipe_to_server] [pipe_from_server] [--get|--set] [color|rate|state] [only for --set: new_value]"
  echo "color values: [RED|GREEN|BLUE]"
  echo "state values: [ON|OFF]"
  echo "rate values: 0..5"
}

function print_error {
  echo $1 1>&2;
}

CLIENT_ID="client_"`date +%s`
echo "client $CLIENT_ID created"
CLIENT_FIFO=`pwd`"/$CLIENT_ID"

REQUEST=$1
PARAMETER=$2
NEW_VALUE=$3

OK=0
FAIL=1

GET=1

NEW_VALUE_INTERNAL=""

function prepare_color_value {
  case "$NEW_VALUE" in
  "RED") INTERNAL_COMMAND+=" red";;
  "GREEN") INTERNAL_COMMAND+=" green";;
  "BLUE") INTERNAL_COMMAND+=" blue";;
  *) print_error "Invalid or missing value for $PARAMETER"; print_usage; exit $FAIL;;
  esac
}

function prepare_state_value {
  case "$NEW_VALUE" in
  "ON") INTERNAL_COMMAND+=" on";;
  "OFF") INTERNAL_COMMAND+=" off";;
  *) print_error "Invalid or missing value for $PARAMETER"; print_usage; exit $FAIL;;
  esac
}

function prepare_rate_value {
  if [[ -z "$NEW_VALUE" ]]; then
    print_error "Missing value for $PARAMETER"
    print_usage; exit $FAIL;
  fi
  INTERNAL_COMMAND+=" $NEW_VALUE"
}

function check_no_parameter {
  if [[ ! -z "$NEW_VALUE" ]]; then
    print_error "Parameter not allowed for request: $REQUEST"
    print_usage
    exit $FAIL
  fi
}

function process_get {
  case "$PARAMETER" in
  "color")  INTERNAL_COMMAND="get-led-color"; check_no_parameter;;
  "rate") INTERNAL_COMMAND="get-led-rate"; check_no_parameter;;
  "state") INTERNAL_COMMAND="get-led-state"; check_no_parameter;;
  *) print_error "Invalid parameter for $REQUEST"; print_usage; exit $FAIL;;
  esac
}

function process_set {
  case "$PARAMETER" in
  "color")  INTERNAL_COMMAND="set-led-color"; prepare_color_value;;
  "rate") INTERNAL_COMMAND="set-led-rate"; prepare_rate_value;;
  "state") INTERNAL_COMMAND="set-led-state"; prepare_state_value;;
  *) print_error "Invalid parameter for $REQUEST"; print_usage; exit $FAIL;;
  esac
}

if [[ "$#" -lt 3 ]]; then
  print_error "Not enough parameters"
  print_usage
  exit $FAIL
fi
 
if [[ ! -p "$PIPE_TO_SERVER" || ! -p "$PIPE_FROM_SERVER" ]]; then
  print_error "Server channels (pipes) not found, check whether server is running"
  exit $FAIL
fi

case "$REQUEST" in
"--get")  process_get;;
"--set")  process_set;;
*) print_error "Invalid request type"; print_usage; exit $FAIL;;
esac

# Send request as background job and block until reply is received.
echo "$INTERNAL_COMMAND" > "$CLIENT_FIFO" & REPLY=`cat $CLIENT_FIFO`

REPLY_ARR=($REPLY)

REPLY_STATUS=${REPLY_ARR[0]}

REPLY_VALUE=${REPLY_ARR[1]}

function prepare_color_output {
  case "$REPLY_VALUE" in
  "red") OUTPUT="RED";;
  "green") OUTPUT="GREEN";;
  "blue") OUTPUT="BLUE";;
  *) print_error "Received unexpected color value: $REPLY_VALUE"; exit $FAIL;;
  esac
}

function prepare_state_output {
  case "$REPLY_VALUE" in
  "on") OUTPUT="ON";;
  "off") OUTPUT="OFF";;
  *) print_error "Received unexpected state value: $REPLY_VALUE"; exit $FAIL;;
  esac
}

function prepare_rate_output {
  if [[ -z "$REPLY_VALUE" ]]; then
    print_error "Missing rate value in the reply"; exit $FAIL;
  fi
  OUTPUT="$REPLY_VALUE"
}

function check_no_reply_value {
  if [[ ! -z "$REPLY_VALUE" ]]; then
    print_error "Received unexpected reply value for $REQUEST request"; exit $FAIL;
  fi
}

function check_reply_value {
  case "$PARAMETER" in
  "color") prepare_color_output;;
  "rate") prepare_rate_output;;
  "state") prepare_state_output;;
  *) ;; # impossible at this point
  esac
}

function process_ok_reply {
  case "$REQUEST" in
  "--set") check_no_reply_value;;
  "--get") check_reply_value;;
  *) ;; # impossible at this point
  esac
  echo "$OUTPUT"
  exit $OK
}

case "$REPLY_STATUS" in
"OK") process_ok_reply;;
"FAILED") exit $FAIL;;
*) print_error "Received unexpected reply status: $REPLY_STATUS"; exit $FAIL;;
esac;

exit $OK

