#!/bin/bash
# This is program for checking all program, which is get persistence in your Linux operating system.
#############
# Constant #
#############
ROOTDIR="/"
ETC_PATH="${ROOTDIR}etc/"
USER_NAME=`stat -c "%U" $(tty)`
HOME_PATH="${ROOTDIR}home/${USER_NAME}/"
BIN_TOOLS="/usr/bin/* /usr/sbin/*"
ROOT_UID="0"
CRON_DIR="${ETC_PATH}rc1.d/ ${ETC_PATH}rc2.d/ ${ETC_PATH}rc3.d/
${ETC_PATH}rc4.d/ ${ETC_PATH}rc5.d ${ETC_PATH}cron.d/ ${ETC_PATH}cron.daily/
${ETC_PATH}monthly.d/ ${ETC_PATH}weekly/ ${ETC_PATH}hourly/ ${ETC_PATH}deny/
${ETC_PATH}anacrontab/ /var/spool/cron/"
CRON_FILES="${ETC_PATH}crontab"
PROFILE_FILES="${ETC_PATH}profile ${ETC_PATH}profile.d/* ${HOME_PATH}.bashrc
${HOME_PATH}.bash_profile"
SERVICE_DIR="/usr/lib/systemd/system/" # /etc/systemd/system/
/run/systemd/system/
INTERNET_TOOLS="url cur curl wget nc get"
EXE_TOOLS="bash csh sh"
ENABLED_SERVICE=`systemctl list-unit-files --state=enabled`
N_ENABLED_SERVICE=`systemctl list-unit-files --state=enabled |wc -l`
ENABLED_DATA=""
MATCHES=""
LOGFILE=""
DATAFILE=""
INTERNET_FOUND=0
EXE_FOUND=0
DATA_UPDATE=0
E_NOTROOT=0
E_BIN=0
E_BIN_FILE=""
E_CHECK_PATERN=0
E_CREATE_TABLE=0
E_CHECK_SHA=0
E_NEW_SERVICE=0
###############
	# Function #
###############
function LogText() {
	# Take first argument to the logfile with data
	if [[ "${LOGFILE}" != "" ]]; then
		CDATE=$(date "+%Y-%m-%d %H:%M:%S");
		echo "${CDATE} $1" >> ${LOGFILE};
	fi
}
function Notice() {
	# This function to display the Security alert to user.
	notify-send -u critical -t 10 $1
	zenity --info --title "Security alert" --text $1 --timeout=15
}
function write_to_table() {
	# To write sha256sum to file data
	if [[ "${DATAFILE}" != "" ]]; then
		if [ $# -ge 1 ]; then
			echo "$1 $2" >> ${DATAFILE}
			else
			E_CREATE_TABLE=1
		fi
		else
		E_CREATE_TABLE=1
	fi
}
function create_table() {
	# Create table with file name DATAFILE.
	if [ ! -z "${BIN_TOOLS}" ]; then
		for TOOLS in ${BIN_TOOLS}; do
			if [ -r ${TOOLS} ]; then
				write_to_table `sha256sum ${TOOLS}` ${TOOLS}
			fi
		done
		E_CREATE_TABLE=2
		else
		E_CREATE_TABLE=1
	fi
}
function update_table() {
	if [ ${E_CREATE_TABLE} -eq 2 ]; then
		rm -f "${DATAFILE}"
	fi
	create_table
}
function check_bin() {
	# Check sha256sum the first argument with data table. The first argument
	is file to check.
	SHA_256=`sha256sum $1`
	MATCHES="$(grep ${SHA_256} ${DATAFILE})"
	if [ $# -ge 1 ]; then
		if [ ! -n "${MATCHES}" ]; then
			E_BIN=1
			E_BIN_FILE=$1
		fi
		else
		E_CHECK_SHA=1
	fi
}
function check_pattern() {
	# Check for existing tools to connect to the internet: nc, wget, curl, get, url,
	cur and execute tools: sh, bash, csh. The first argument is file to check.
	if [ $# -eq 1 ]; then
		for TOOLS in ${INTERNET_TOOLS}; do
			MATCHES="$(grep ${TOOLS} $1)"
			if [ -n "$MATCHES" ]; then
				INTERNET_FOUND=1
			fi
		done
		for TOOLS in ${EXE_TOOLS}; do
			MATCHES="$(grep ${TOOLS} $1)"
			if [ -n "$MATCHES" ]; then
				EXE_FOUND=1
			fi
		done
		else
		E_CHECK_PATERN=1
	fi
}
function check_service() {
	# Compare number of enabled services with the past (from the start of program).
	Take no argument.
	TMP_FILE="/tmp/enabled_service.txt"
	N_NOW=`systemctl list-unit-files --state=enabled |wc -l`
	# Note: Actual number of enabled service is N_NOW - 3
	if [ ${N_NOW} -gt ${N_ENABLED_SERVICE} ]; then
		if [ -f "${TMP_FILE}" ]; then
			rm -f "${TMP_FILE}"
		fi
		echo "${ENABLED_SERVICE}" >> "${TMP_FILE}";
		NEW_ENABLED=`diff "${ENABLED_DATA}" "${TMP_FILE}" |grep -oE
		'[[:alnum:]_-?~#.+/]*.service|[[:alnum:]_-?~#.+/]*.target|[[:alnum:]_-
		?~#.+/]*.socket'`
		if [ ! -z "${NEW_ENABLED}" ]; then
			for I in "${NEW_ENABLED}"; do
				LogText "Detected new enabled service "${I}""
				Notice "Detected new enabled service in
				"${SERVICE_DIR}""${I}""
			done
		fi
	fi
}
function check_root {
	if [ "$UID" -ne "$ROOT_UID" ]; then
		LogText "Run in user mode"
		E_NOTROOT=1
		else
		LogText "Run in root mode"
	fi
}
finish() {
	LogText "Service audit persistence finished."
	exit 0
}
############
	# Main #
############
if [[ "$1" == "--update" ]]; then
	# Flag update is used for update sha256 check table and list enabled service.
	DATA_UPDATE=1
fi
trap finish SIGINT
check_root
if [ -z "${LOGFILE}" ]; then
	# Creat a log file in temporary directory
	if [ ! -f /tmp/audit_persistence.log ]; then
		touch /tmp/audit_persistence.log
		if [ $? -eq 0 ]; then
			LOGFILE="/tmp/audit_persistence.log";
			else
			LOGFILE="/dev/null";
		fi
		else
		LOGFILE="/tmp/audit_persistence.log"
	fi
fi
if [ ${E_NOTROOT} -eq 1 ]; then
	# Creat a data file (sha256sum) in usr directory
	if [ ! -f "${HOME_PATH}"sha256-data-nonroot ]; then
		touch "${HOME_PATH}"sha256-data-nonroot
		if [ $? -eq 0 ]; then
			DATAFILE=""${HOME_PATH}"sha256-data-nonroot";
			create_table
			LogText "Created sha256 nonroot table"
			else
			DATAFILE="/dev/null";
			LogText "Create sha256 nonroot table fail"
		fi
		elif [ "${DATA_UPDATE}" -eq 1 ]; then
		DATAFILE=""${HOME_PATH}"sha256-data-nonroot";
		update_table
		LogText "Updated sha256 nonroot table"
		else
		LogText "No updated sha256 nonroot table"
	fi
	elif [ ! -f "${HOME_PATH}"sha256-data-root ]; then
	touch "${HOME_PATH}"sha256-data-root
	if [ $? -eq 0 ]; then
		DATAFILE=""${HOME_PATH}"sha256-data-nonroot";
		create_table
		LogText "Created sha256 table with root"
		else
		DATAFILE="/dev/null";
		LogText "Create 256sha root table fail"
	fi
	elif [ ${DATA_UPDATE} -eq 1 ]; then
	DATAFILE=""${HOME_PATH}"sha256-data-nonroot";
	update_table
	LogText "Updated sha256 root table"
	else
	LogText "No updated sha256 root table"
fi
# Create table of service if system using systemd
CHECK_SYSTEMD=`pidof systemd`
if [ ${CHECK_SYSTEMD} -eq 1 ]; then # System used systemd
	N_ENABLED_SERVICE=`systemctl list-unit-files --state=enabled |wc -l`
	if [ ! -f "${HOME_PATH}"listservice.txt ]; then
		touch "${HOME_PATH}"listservice.txt
		if [ $? -eq 0 ]; then
			ENABLED_DATA=""${HOME_PATH}"listservice.txt";
			echo "${ENABLED_SERVICE}" >> "${ENABLED_DATA}";
			LogText "Created file list service"
			else
			ENABLED_DATA="/dev/null";
			LogText "Create file list service fail"
		fi
		elif [ "${DATA_UPDATE}" -eq 1 ]; then
		ENABLED_DATA=""${HOME_PATH}"listservice.txt"
		rm -f "${ENABLED_DATA}"
		echo "${ENABLED_SERVICE}" >> "${ENABLED_DATA}"
		LogText "Updated file list service"
		else
		LogText "No updated file list service"
	fi
fi
while true; do
	if [ ${CHECK_SYSTEMD} -eq 1 ]; then
		check_service
	fi
	for TOOLS in ${BIN_TOOLS}; do
		check_bin "${TOOLS}"
		if [ ${E_BIN} -eq 1 ]; then
			LogText "The shell "${TOOLS}" was changed!"
			Notice "The shell "${TOOLS}" was changed!"
		fi
	done
	for SHEL in ${CRON_FILES}; do
		check_pattern "${SHEL}"
		if [ ${EXE_FOUND} -eq 1 && ${INTERNET_FOUND} -eq 1]; then
			LogText "Detected "${SHEL}" used executed tools to
			connect the internet"
			Notice "Detected "${SHEL}" used executed tools to
			connect the internet"
		fi
	done
	sleep 5 &
	wait
done;