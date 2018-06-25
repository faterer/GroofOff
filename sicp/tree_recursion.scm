;;;fibonacci numbers
;;;recursion procedure
(define (fib n)
  (cond ((= n 0) 0)
        ((= n 1) 1)
        (else (+ (fib (- n 1)) 
                 (fib (- n 2))))))

;;;iterative procedure
(define (fib n) (fib-iter 1 0 n))
(define (fib-iter a b count)
  (if (= count 0) b
      (fib-iter (+ a b) a (- count 1))))


;;;How many different ways can we make change of $1.00(100 cents), given half-dollar(50),quarters(25),dimes(10),nickels(5), and pennis(1) 

amount a using n kinds of coins equals
1. the number of ways to change amount a using all but the first kind of coin plus
2. the number of ways to change amount (a - d) using all n kinds of coins, where d is the denomination of first kind of coin

(define (count-change amount) (cc amount 5))

(define (cc amount kinds-of-coins)
    (cond ((= amount 0) 1)
          ((or (< amount 0) (= kinds-of-coins 0)) 0) 
          (else (+ (cc amount (- kinds-of-coins 1))
                   (cc (- amount (first-denomination kinds-of-coins)) kinds-of-coins))))) 
                 
(define (first-denomination kinds-of-coins)
(cond ((= kinds-of-coins 1) 1) 
      ((= kinds-of-coins 2) 5)        
      ((= kinds-of-coins 3) 10)
      ((= kinds-of-coins 4) 25)
      ((= kinds-of-coins 5) 50)))