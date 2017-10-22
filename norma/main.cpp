#include <cstdio>

/*
    How do u solve this problem?

    Ok. Let the upper bound be r.
    So r ranges from 1 to N.

    Let's define s(r) as
    the sum of the operation on all sequences
    with a highest index no greater than r.

    How is s(r) related to s(r+1)?

    Well, s(r+1)=s(r)+sum of operation on all sequences ending in r+1.

    In a sequence p, r+1 may be important, or unimportant.

    We define important in sequence p if r+1 is greater than the maximum, 
    or less than the minimum in the sequence p, excluding r+1.

    So each time r+1 is unimportant, it is just the previous one, times (l+1)/l
    cuz there's one extra term.

    Note r+1 is important on sequence r+1. 
    If r+1 is unimportant on sequence a...(r+1), it is unimportant on any b < a.

    So there exists a largest index k such that r+1 is important. 

    Ok...
    But even if k = r+1 (i.e., r+1 is unimportant for all sequences other than itself)
    how do you compute it? Fuck.

    What do you need to compute s(r+1)? 

    Every time you add r+1, there exists 1 <= k <= r+1 such that for all 1 <= i < k, 
    r+1 is unimportant and for all i >= k, r+1 is important.

    Can you precompute this k for each r+1?... ok let's say you can.
    Then what.

    1, 2, 3, ..., k, k+1, ..., r-1, r, r+1

    T[i] to T[b-1] holds the length, min, and max of i to b-1. 

    But it can't really, because that takes linear time to update and query.

    Well first of all, length is initially set to zero, and every time, you increment by one.

    Let's say you add A[b]. Then before some k, 1 <= k <= b, all values of min and max stay the same. 
    For all values of i, k <= i <= b, either you set min to A[b], or max to A[b] (note that if i==k, 
    A[b] is both minimum and maximum). 

    ok... let's assume you have precomputed k[i] for 1 <= i <= N (although this might be pretty difficult...).

    How would you do the update? Some kind of binary indexed tree. But the sum is a bit odd,
    because it isn't just a sum, but a sum of products where each term is updated dynamically. 
    
    They think so logically!

    You need a data structure that supports updating after some value
    // case = 0, or 1
    update(lo, hi, val, case) 
    // for each lo <= i <= hi, 
        // if case = 0
            // small[i] = val
        // else if case = 1
            // big[i] = val

    increment(lo, hi)
    // for each 1 <= i < lo, 
        // l[i]++;
    
    query(hi)
    // sum=0
    // for 1 <= i <= hi
        // sum += l[i]*small[i]*big[i]
    // return sum

    You need a data structure that supports each of these in logarithmic time (?)
    Sort of like range updates. Except the one weird thing is query. It is a sum of prod.
    Well once you update, you can factor out small[i] or big[i] does that help?

    Idea 1:
        Store the products in a BIT.
        increment (lo, hi) runs logarithmically on each lo to hi, which is linear * log.
        Slow af. 

*/