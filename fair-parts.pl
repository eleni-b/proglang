read_line(Stream, List) :-
    read_line_to_codes(Stream, Line),
    atom_codes(A, Line),
    atomic_list_concat(As, ' ', A),
    maplist(atom_number, As, List).

read_and_return(File, N, Weights) :-
    open(File, read, Stream),
    read_line(Stream, [M, N]),
    read_line(Stream, Weights),
    length(Weights, L),
    ( L =:= M -> close(Stream)  %% just a check for for sanity
    ; format("Error: expected to read ~d weights but found ~d", [M, L]),
      close(Stream), fail
    ).


required_k ([]], n, x, total) :- 0.
required_k ([H|T], n, x, total, thisK) :- new_total is total + H, 
	(new_total > x) -> required_k(T, n, x, H, thisK+1);
	not(new_total > x) -> required_k(T, n, x, total, thisK).


/* Binary search code, as seen in rosettacode.org */

bin_search(Elt,List,Result):-
  length(List,N), bin_search_inner(Elt,List,1,N,Result).
 
bin_search_inner(Elt,List,J,J,J):-
  nth(J,List,Elt).

bin_search_inner(Elt,List,Begin,End,Mid):-
  Begin < End,
  Mid is (Begin+End) div 2,
  nth(Mid,List,Elt).

bin_search_inner(Elt,List,Begin,End,Result):-
  Begin < End,
  Mid is (Begin+End) div 2,
  required_k(List,N,Mid,0,thisK),
  new_K is thisK+1,
  new_K > Elt,
  NewBegin is Mid+1,
  bin_search_inner(Elt,List,NewBegin,End,Result).

bin_search_inner(Elt,List,Begin,End,Result):-
  Begin < End,
  Mid is (Begin+End) div 2,
  required_k(List,N,Mid,0,thisK),
  new_K is thisK+1,
  not(new_K > Elt),
  NewEnd is Mid,
  bin_search_inner(Elt,List,Begin,NewEnd,Result).


/* End of binary search */


my_printer([],Lout,_,_,Tl,[Lout|Tl]).
my_printer([H|T],Lout,Sum,Li,Tl,Res) :- S1 is H + Sum,
  (S1 > Li -> my_printer([H|T],[],0,Li,[Lout|Tl],Res);
   not(S1 > Li) -> my_printer(T,[H|Lout],S1,Li,Tl,Res) ).

  
fair_parts (File, Result) :- 
  read_and_return(File,K,W),sum_list(W,R1),max_list(W,L1),
  take(K-1,W,Part1),drop(K-1,W,Part2),sum_list(Part2,S),max_list(Part1,M),
  max_list([S,M],R2),L2 is R1/K,max_list([L1,L2],L),min_list([R1,R2],R),Li is (L + R)/2
  ,my_finder(W,0,Li,1,Parts),Diff is R - L,my_finder2(W,K,Diff,Li,L,R,Res),
  my_finder(W,0,Res,1,Parts1),my_printer(W,[],0,Res,[],Res1).

  max_list(W,MAX), sum_list(W,SUM), 

	
