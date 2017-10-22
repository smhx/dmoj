var Q=48; 

var N = 0;

const periods = [35, 100, 10];
const rewards = [30, 60, 9];
var turns = [4, 11, 5];

while (Q > 0) {
    Q--;
    if (turns[N%3]==periods[N%3]) {
        Q += rewards[N%3];
        turns[N%3] = 0;
    }
    turns[N%3]++;
    N++;
}

console.log("Martha plays %d times before going broke.", N);
