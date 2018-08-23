dec2tern(W,[]):- W =0,!.
dec2tern(W,[H|T]):- Remm is mod(W, 3),Quot is div(W, 3),Remm = 2,Q is Quot+1,H = -1,dec2tern(Q,T). 
dec2tern(W,[H|T]) :- Remm is mod(W, 3),Quot is div(W, 3),Remm = 1,H = 1,dec2tern(Quot,T).
dec2tern(W,[H|T]) :- Remm is mod(W, 3),Quot is div(W, 3),Remm = 0,H = 0,dec2tern(Quot,T).

move_right([H1|T1],Ind,[H|T]) :- (H1 =:= 1 -> H = Ind,Indd is Ind + 1,move_right(T1,Indd,T)
					; H1 \= 1 -> Indd is Ind +1,move_right(T1,Indd,[H|T])).

move_right(_,_,[]) :- !.

move_left([H1|T1],Ind,[H|T]) :- (H1 =:= -1 -> H = Ind,Indd is Ind + 1,move_left(T1,Indd,T)
					; H1 \= -1 -> Indd is Ind +1,move_left(T1,Indd,[H|T])).

move_left(_,_,[]) :- !.

balance2(N, W, L, R) :- dec2tern(W,Lst),length(Lst,C),(N >= C -> once(move_left(Lst,1,L)),once(move_right(Lst,1,R));
N < C -> 1 = 0).
balance(N,W,L,R) :- once(balance2(N,W,L,R)).