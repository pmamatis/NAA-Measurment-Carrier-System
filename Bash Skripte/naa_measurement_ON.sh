#! /bin/bash
# shellcheck source=/dev/null
source config.sh
mosquitto_pub -h ${Broker_IP} -t "Config/${Board_MAC_1}/ON_OFF" -m "ON"
