#!/bin/zsh


###########################     CHAMPION VALIDE
valid=(
"42" 
"Asombra"
"Car"
"Douceur_power"
"Explosive_Kitty"
"Gagnant"
"Kappa"
"Kittystrophic"
"Machine-gun"
"MarineKing"
"Misaka_Mikoto"
"Octobre_Rouge_V4.2"
"Rainbow_dash"
"Survivor"
"THUNDER"
"Varimathras"
"Wall"
"_honeybadger"
"aff_no_OCP"
"barriere"
"bee_gees"
"bigzork"
"casimir"
"champ"
"comment_len_2048"
"corelol"
"darksasuke"
"doge"
"dubo"
"end_comment"
"ex"
"ex1"
"flipped_name_comment"
"fluttershy"
"gateau"
"gedeon"
"hash_and_tab_at_EOF"
"hash_at_header"
"helltrain"
"jinx"
"jumper"
"justin_bee"
"littlepuppy"
"live"
"loose"
"mandragore"
"maxidef"
"meowluigi"
"mise_a_jour_windows95"
"mortel"
"name_len_128"
"neg_indirect_error"
"nl_at_header"
"nl_at_header_flipped"
"no_space_between_op_and_param"
"overwatch"
"run_Kitty_RUN"
"salamahenagalabadoun"
"sam_2.0"
"skynet"
"slider2"
"sq_at_header"
"tab_at_end_of_file"
"terminator"
"toto"
"turtle"
"ultima"
"ultimate-surrender"
"weirdest_error_ever"
"youforkmytralala"
"zork"
)
##################      CHAMPION INVALIDE
invalid=(
"big_feet"
"comment_len_2049"
"direct_param_no_value"
"empty_namecomment"
"four_arg_malloc_free_pointer_error"
"header_double_comments"
"header_double_names"
"header_max_comment"
"header_max_name"
"header_nl"
"header_nl_unclosed"
"header_null_name"
"label_contain_badchar"
"label_error_1"
"label_error_2"
"label_error_3"
"label_invalidname"
"label_noending"
"label_space"
"label_without_double_dot_at_the_end"
"name_len_129"
"op_double_operation_on_single_line"
"op_extra"
"op_extreme"
"op_no_code"
"param_badtypes"
"param_commas"
"param_direct_no_sp"
"param_direct_no_value"
"param_double_commas"
"param_extra2"
"param_mt_3"
"param_mt_r99"
"param_nonexistent_label"
"param_plus_minus"
"param_specialchars"
"zother_1"
"zother_2"
"zother_3"
"zother_4"
)
if [ ! "$1" ]
then
	clear
	printf "\033[032margument attendu\033[0m\n"
	printf "\033[031m1:\033[0m champion valide\n"
	printf "\033[031m2:\033[0m champion invalide\n"
	printf "\033[031mNo other\033[0m\n"
elif [ $1 -eq 1 ]
then
    for map in ${valid[*]}
    do
        clear
        printf "\033[032m${map}\033[0m\n"
		printf "\033[035m############# MOI  ##############\033[0m\n"
        valgrind --leak-check=full --track-origins=yes ./asm valid/${map}.s
		#Valgrind ./asm valid/${map}.s
		printf "\033[036m############# GOOD ##############\033[0m\n"
		./zaz_asm valid2/${map}.s
        xxd valid/${map}.cor > xxd
		xxd valid2/${map}.cor > zaz_xxd
        if diff xxd zaz_xxd;then  
            printf "\n|-> \033[32m${map} OK\033[0m\n"
        else
	        printf "\n|-> \033[31m${map} K.O.\033[0m\n"
        fi
		echo "Press enter key for next test or exit with [ctrl + c]"
		read a
		rm -rf valid/${map}.cor
		rm -rf valid2/${map}.cor
		echo > xxd
		echo > zaz_xxd
    done
elif [ $1 -eq 2 ]
then
    for map in ${invalid[*]}
        do
            clear
            printf "\033[032m${map}\033[0m\n"
			printf "\033[035m############# MOI  ##############\033[0m\n"
            Valgrind ./asm error/${map}.s
			printf "\033[036m############# GOOD ##############\033[0m\n"
			./zaz_asm error2/${map}.s
			echo "Press enter key for next test or exit with [ctrl + c]"
			read a
            #read -p "Press enter key for next test or exit with [ctrl + c]"
    done
else
	clear
	printf "\033[032margument attendu\033[0m\n"
	printf "\033[031m1:\033[0m champion valide\n"
	printf "\033[031m2:\033[0m champion invalide\n"
	printf "\033[031mNo other\033[0m\n"
fi	