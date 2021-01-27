
chmod +x ./firewall.sh
while read packet; do
	while read cur_line; do
		cur_line=$(echo "$cur_line" | tr -d ' ') # Remove spaces
		cur_line=$(echo "$cur_line" | sed -e 's/#.*//') # Remove comments
		if [[ "" != "$cur_line" ]]; then
			IFS=',' read -r -a rules_array <<< "$cur_line" # Split by delimiter
			for i in "${rules_array[@]}"; do
				echo "$packet" | ./firewall.exe "$i" >> packet_tmp.txt # Send packet to program
			done
			counter=$(cat packet_tmp.txt | wc -l) # Count number of elements
			if [[ counter -eq ${#rules_array[@]} ]]; then
				echo "$packet" >> packets_to_print.txt
			fi
			> packet_tmp.txt
		fi
	 done < "$1"
done
	cat packets_to_print.txt | sort | uniq | sed '/^$/d' | tr -d ' ' # Trim and print packets
	rm packet_tmp.txt packets_to_print.txt # Remove helper text files
