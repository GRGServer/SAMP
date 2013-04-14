#! /bin/bash

ARGS=`getopt -o "a:e:v" -l "action:,environment:,rev:,svn-baseurl:,svn-password:,svn-username:,tag:,verbose" -n "sampmgr" -- "$@"`

if [ $? -ne 0 ]; then
	exit 1
fi

# Some magic for getopt
eval set -- "$ARGS"

# Default values for option variables
REVISION="HEAD"
SVNBASEURL="http://svn.selfcoders.com/grgserver"
SVNPASSWORD="tPEOPPJXPCJg9eMx9heu"
SVNUSERNAME="samp"

# Get options
while true; do
	case "$1" in
		-a | --action)
			ACTION="$2"
			shift 2
		;;

		-e | --environment)
			ENVIRONMENT="$2"
			shift 2
		;;

		--rev)
			REVISION="$2"
			shift 2
		;;

		--svn-baseurl)
			SVNBASEURL="$2"
			shift
		;;

		--svn-password)
			SVNPASSWORD="$2"
			shift
		;;

		--svn-username)
			SVNUSERNAME="$2"
			shift
		;;

		--tag)
			TAG="$2"
			shift 2
		;;

		-v | --verbose)
			VERBOSE=1
			shift 1
		;;

		--)
			shift 1
			break
		;;
	esac
done

function compilePawn
{
	cd $SAMPPATH/$1
	for FILE in *.pwn; do
		if test -f $FILE; then
			echo "Compiling $1/$FILE..."
			wine $PAWNCC $FILE -i../includes -\; -\( COMPILE_SERVER=1
		fi
	done
}

function printVerbose
{
	if [ "$VERBOSE" ]; then
		echo $@
	fi
}

function showUsage
{
	echo ""
	echo "  Usage: sampmgr options"
	echo ""
	echo "  Required options:"
	echo "    -e | --environment   Specify the environment"
	echo "    -a | --action        Specify the action"
	echo ""
	echo "  Optional options:"
	echo "    -v | --verbose       Output more information (For debugging)"
	echo ""
	echo "  Advanced optional options:"
	echo "         --svn-baseurl   Change the SVN base URL from '$SVNBASEURL' to another one"
	echo "         --svn-password  Change the SVN password from '********' to another one"
	echo "         --svn-username  Change the SVN username from '$SVNUSERNAME' to another one"
	echo ""
	echo "  Available environments:"
	echo "    dev                  The development SAMP-Server at port 7776"
	echo "    live                 The live SAMP-Server at port 7777"
	echo ""
	echo "  Available actions:"
	echo "    livelog              Show log using tail -f"
	echo "    log                  Output complete server log file"
	echo "    restart              Stop and restart the SAMP-Server"
	echo "    start                Start the SAMP-Server"
	echo "    status               Show the current running status of the SAMP-Server"
	echo "    stop                 Stop the SAMP-Server"
	echo "    update               Checkout SAMP-Server from SVN and compile PWN files using pawncc"
	echo "                         In environment 'dev' you can optionally use the -rev option to specify the SVN revision"
	echo "                         In environment 'live' you have to use the -tag option to specify the tag in SVN"
	echo "    wipe                 Delete all SAMP-Server files"
	echo ""
	echo "  Examples:"
	echo "    sampmgr --environment dev --action start"
	echo "    sampmgr -e dev --action update -rev 800"
	echo "    sampmgr -e live -a update -tag public-beta-1.0"
	echo ""
}

if [ "$ENVIRONMENT" = "" ]; then
	showUsage
	exit
fi

case "$ENVIRONMENT" in
	dev)
	;;

	live)
	;;

	*)
		echo "Invalid environment: $ENVIRONMENT"
		echo ""
		echo "Available environments:"
		echo "  dev   The development SAMP-Server at port 7776"
		echo "  live  The live SAMP-Server at port 7777"
		echo ""
		exit
	;;
esac

SAMPPATH="/opt/samp/$ENVIRONMENT"
ANNOUNCEEXECUTABLE="$SAMPPATH/announce"
NPCEXECUTABLE="$SAMPPATH/samp-npc"
SERVEREXECUTABLE="$SAMPPATH/samp-srv"
PAWNCC="$SAMPPATH/tools/pawn/pawncc.exe"
PIDFILE="/var/run/samp-$ENVIRONMENT.pid"
LD_LIBRARY_PATH="$SAMPPATH:/usr/lib:$LD_LIBRARY_PATH"
STOPTIMEOUT=15

DAEMONCMD_START="start-stop-daemon --start --pidfile $PIDFILE --startas $SERVEREXECUTABLE --chuid samp --chdir $SAMPPATH --make-pidfile --background"
DAEMONCMD_STOP="start-stop-daemon --stop --pidfile $PIDFILE --retry $STOPTIMEOUT"

if [ "$VERBOSE" ]; then
	DAEMONCMD_START="$DAEMONCMD_START --verbose"
	DAEMONCMD_STOP="$DAEMONCMD_STOP --verbose"
else
	DAEMONCMD_START="$DAEMONCMD_START --quiet"
	DAEMONCMD_STOP="$DAEMONCMD_STOP --quiet"
fi

DAEMONCMD_TESTRUNNING="$DAEMONCMD_START --test"

export LD_LIBRARY_PATH

case "$ACTION" in
	livelog)
		tail -f $SAMPPATH/server_log.txt
	;;

	log)
		cat $SAMPPATH/server_log.txt
	;;

	restart)
		$0 --environment $ENVIRONMENT --action stop
		if [ $? = 0 ]; then
			$0 --environment $ENVIRONMENT --action start
			if [ $? -ne 0 ]; then
				exit 1
			fi
		else
			exit 1
		fi
	;;

	start)
		echo "Starting SAMP-Server ($ENVIRONMENT)..."
		$DAEMONCMD_START
		case "$?" in
			0)
				echo "Done"
			;;

			1)
				echo "Already running!"
				exit 1
			;;

			*)
				echo "Failed"
				exit 1
			;;
		esac
	;;

	status)
		$DAEMONCMD_TESTRUNNING
		case "$?" in
			0)
				echo "SAMP-Server ($ENVIRONMENT) is not running"
			;;

			1)
				echo "SAMP-Server ($ENVIRONMENT) is running"
			;;

			*)
				echo "An error occurred!"
				exit 1
			;;
		esac
	;;

	stop)
		echo "Stopping SAMP-Server ($ENVIRONMENT)..."
		$DAEMONCMD_STOP
		case "$?" in
			0)
				echo "Done"
			;;

			1)
				echo "Not running!"
			;;

			*)
				echo "Failed"
				exit 1
			;;
		esac
	;;

	update)
		case "$ENVIRONMENT" in
			dev)
				mkdir -p $SAMPPATH
				svn checkout $SVNBASEURL/trunk $SAMPPATH -r $REVISION --non-interactive --username $SVNUSERNAME --password $SVNPASSWORD
			;;

			live)
				if [ "$TAG" = "" ]; then
					echo "Option -tag <tag-name> is required!"
					exit 1
				fi
				mkdir -p $SAMPPATH

				svn info $SAMPPATH --non-interactive --username $SVNUSERNAME --password $SVNPASSWORD > /dev/null 2>&1
				if [ $? = 0 ]; then
					printVerbose "Switching to tag '$TAG'"
					svn switch $SVNBASEURL/tags/$TAG $SAMPPATH --non-interactive --username $SVNUSERNAME --password $SVNPASSWORD
				else
					printVerbose "Checking out tag '$TAG'"
					svn checkout $SVNBASEURL/tags/$TAG $SAMPPATH -r $REVISION --username $SVNUSERNAME --password $SVNPASSWORD
				fi

				# Change server.cfg
				sed -i 's/port 7776/port 7777/' $SAMPPATH/server.cfg
				sed -i '/^password/d' $SAMPPATH/server.cfg
			;;

			*)
				exit 1
			;;
		esac

		REVISION=`svn info $SAMPPATH --non-interactive --username $SVNUSERNAME --password $SVNPASSWORD | sed -nr 's/Last Changed Rev: ([0-9]+)/\1/p'`
		COMMITTER=`svn info $SAMPPATH --non-interactive --username $SVNUSERNAME --password $SVNPASSWORD | sed -nr 's/Last Changed Author: (.*)/\1/p'`

		CUSTOMINC="$SAMPPATH/includes/grgserver/main_server.inc"
		echo "// Generated using sampmgr" > $CUSTOMINC
		echo "" >> $CUSTOMINC
		echo "#define COMPILER_DATE \"`date +%Y-%m-%d`\"" >> $CUSTOMINC
		echo "#define COMPILER_TIME \"`date +%H:%M:%S`\"" >> $CUSTOMINC
		echo "#define COMPILER_SVN_REVISION $REVISION" >> $CUSTOMINC
		echo "#define COMPILER_SVN_LASTCOMMITTER \"$COMMITTER\"" >> $CUSTOMINC
		echo "" >> $CUSTOMINC
		echo "#include <grgserver\\main.inc>" >> $CUSTOMINC

		compilePawn filterscripts
		compilePawn gamemodes
		compilePawn npcmodes

		# Generate commands.txt
		COMMANDLIST="$SAMPPATH/scriptfiles/commands.txt"
		rm -f $COMMANDLIST
		cd $SAMPPATH/includes/grgserver/Commands
		for FILE in *.inc; do
			sed -nr 's/^CMD:([a-zA-Z0-9]+)\(([^,]+),([^,]+),([ 0-9]+)\)/- \1  \4/p' $FILE >> $COMMANDLIST
			sed -nr 's/^PCMD:([a-zA-Z0-9]+)\[([A-Z]+)\]\(([^,]+),([^,]+),([ 0-9]+)\)/P \1 \2 \5/p' $FILE >> $COMMANDLIST
		done

		svn log -l 1 $SAMPPATH  --non-interactive --username $SVNUSERNAME --password $SVNPASSWORD > $SAMPPATH/scriptfiles/update_log

		chown -R samp:samp $SAMPPATH
		chmod +x $ANNOUNCEEXECUTABLE
		chmod +x $NPCEXECUTABLE
		chmod +x $SERVEREXECUTABLE
	;;

	wipe)
		rm -Rfv $SAMPPATH
		mkdir -v $SAMPPATH
		chown -R samp:samp $SAMPPATH
	;;

	*)
		showUsage
		exit 1
	;;
esac