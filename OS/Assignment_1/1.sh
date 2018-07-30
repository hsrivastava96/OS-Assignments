#!/bin/bash

#Demonstration script

#run it by typing sh 1.sh in the containing folder

#CREATE
create()
{
	printf 'Please enter name for your addressbook --> '
	read -r fname

	if [ -e $fname ]
	then 
		echo "EXISTS!!!"
	else
		touch $fname
		echo "CREATED"
	fi
}

#INSERT
insert()
{
	printf 'Please enter your name --> '
	read -r name

	printf 'Please enter your class --> '
	read -r class

	printf 'Please enter your roll --> '
	read -r roll

	printf 'Please enter your city --> '
	read -r city
	
	echo $name $class $roll $city >> $fname 
}

#VIEW ADDRESSBOOK
display()
{
	echo "**********ADDRESS BOOK**********"
	cat $fname
}

#DELETE
delete()
{
	printf 'Please enter the name of the record to be deleted --> '
	read -r del_rec
	grep -v "^$del_rec" $fname >> new_file.txt
	cp new_file.txt $fname
	rm new_file.txt
	echo "Modified Database"
	cat $fname
}

#SEARCH
search()
{
	printf 'Please enter the name of the record to be searched --> '
	read -r searched
	grep -i "^$searched" $fname
}

#MODIFY
modify()
{
	printf 'Please enter the name of the record to be modified --> '
	read -r mod
	grep -i "^$mod" $fname
	grep -v "^$mod" $fname >> nfile.txt
	cp nfile.txt $fname
	rm nfile.txt
	echo "Please enter new details of the record"
	insert
	echo "Updated database"
	cat $fname
}

#MAIN
cond=1
while [ $cond -eq 1 ];
do
	echo "1. Create Address Book"
	echo "2. Insert record in Address Book"
	echo "3. Display Address Book"
	echo "4. Delete record from Address Book"
	echo "5. Modify record in Address Book"
	echo "6. Search record in Address Book"
	echo "7. Exit"
	
	printf 'Please enter your choice --> '
	read -r choice

	case $choice in
		1) echo "#CREATE ADDRESS BOOK"
		   create
		;;
		2) echo "#INSERT RECORD"
		   insert
		;;
		3) echo "#DISPLAY ADDRESS BOOK"
		   display
		;;
		4) echo "#DELETE RECORD"
		   delete
		;;
		5) echo "#MODIFY RECORD"
		   modify
		;;
		6) echo "#SEARCH RECORD"
		   search
		;;
		7) exit 0
		;;
	esac

	printf 'Do you want to continue? Yes=1, No=0 (1/0) --> '
	read -r cond
done
exit 0
