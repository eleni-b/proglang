open Printf;;
include Str;;
open Str;;


let rec sum list =
    match list with
    | [] -> 0
    | h::t -> h + (sum t);;

let rec max_list list =
    match list with
    | [] -> 0
    | h::t -> max h (max_list t);;


let rec required_k list n x total =
    match list with
    | [] -> 0
    | h::t ->
        let total = total + h in
        if (total > x) then
                1 + required_k t n x h
        else
            required_k t n x total;;


let rec binsearch n list lo hi k =
    if (hi <= lo) then
        lo
    else
        let mid = lo + (hi-lo)/2 in
        let requiredK = (required_k list n mid 0) + 1 in
            if (requiredK <= k) then
                binsearch n list lo mid k
            else
                binsearch n list (mid+1) hi k;;

(* First, we divide the given sequence in intervals of length smaller than total, given that total is the minmax sum, as it occured from the binary search-like process above. To acomplish that, we use the create_list function. After that step, we use the function modify_string, if the number of pieces is less than the desired k. If the above is true (times<k), we start creating intervals of length 1 from the beginning of the string, so as to minimize the weights of the first intervals.*)

let rec modify_string str k acc times i  =
    if (times < k) then
        let acc = acc ^ (String.make 1 str.[i]) ^ " | " in
            modify_string str k acc (times+1) (i+2)
    else
        let new_str = (String.sub str i ((String.length str)-i)) in
            acc ^ new_str;;

            


let rec create_list x list total acc times k =
    match list with
    | [] -> modify_string acc k "" times 0
    | h::t ->
        let total = total + h in
        if (total <= x) then
        begin
            let str = string_of_int h ^ " " ^ acc in
            create_list x t total str times k
        end
        else begin
            let str = string_of_int h ^ " | " ^ acc in
            create_list x t h str (times+1) k
        end;;



let () =
    let file = Sys.argv.(1) in
        let ic = open_in file in
        try
            let line1 = input_line ic in
            let n_k = List.map int_of_string (Str.split (Str.regexp " ") line1) in
            let n = List.nth n_k 0 in
            let k = List.nth n_k 1 in
            let line2 = input_line ic in
            let list = List.map int_of_string (Str.split (Str.regexp " ") line2) in
            let x = (binsearch n list (max_list list) (sum list) k) in
                print_string (create_list x (List.rev list) 0 "" 1 k );
                print_string "\n";
                close_in ic
        with e ->
            close_in_noerr ic;
            raise e;;
