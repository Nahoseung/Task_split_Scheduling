### Task split을 활용한 Semi Pratiotioned Scheduling Algorithm SPA1,SPA2 구현


task set (C,T)
{
Task 1 : (3,10) (0.3)
Task 2 : (15,20) (0.75)
Task 3 : (2,20) (0.1)
Task 4 : (2,20) (0.1)
}

(N=4) Utilization Bound = 0.756828
(N=4) Light Task Bound = 0.430792 (보다 작으면 Light task)

--------------------------------------------------------------

*SPA1
1. Task 4 ->P1		        (0.0 -> 0.1)

2. Task 3 ->P2		        (0.0 -> 0.1)

3. Task 2 ->P1		        (0.1 + 0.7 > Utilization Bound  : 할당 불가.)

	Task2 split  -> Task2(Body: 0.65) + Task2(Tail: 0.1)

4. Task2 (Body) ->P1 	    (0.1 -> 0.75 = Utilization Bound)

4. Task 2(Tail) -> P2 	 	(0.1 -> 0.2)

5. Task 1 -> P2	 	        (0.2 -> 0.5)

P1 : Task2(Body) / Task4 		    (0.75)
P2 : Task1 / Task2 (Tail) / Task3 	(0.5)
-> Task2 (Tail)이 더 높은 우선 순위인 Task1의 간섭으로 인해 Scheduling 불가능
--------------------------------------------------------------

*SPA2
1. Pre-assign: Task2 -> P1 	(0.0 -> 0.75)

2. Task4 -> P1		        (0.0 -> 0.1)

3. Task3 -> P1		        (0.1 -> 0.2)

4. Task1 -> P1		        (0.2 -> 0.5)

P1 : Task2 			            (0.75)
P2 : Task1 / Task3 / Task4		(0.5)	
-> 모든 Task가 Scheduling 가능