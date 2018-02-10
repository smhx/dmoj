/*input
5
21 -10 7 3 18
*/
import java.util.*;

public class Main {
    static Random rand;

	static void swap(int a[], int i, int j) {
		int tmp = a[i];
		a[i] = a[j];
		a[j] = tmp;
	}

	static int partition(int A[], int l, int r, int pivot) {
		int i = l, j = r;
		while (i<j) {
			while (i < pivot && A[i] <= A[pivot]) ++i;
			while (j > pivot && A[j] >= A[pivot]) --j;
			if (i==pivot) {
				pivot = j;
			} else if (j==pivot) {
				pivot = i;
			} 
			swap(A, i, j);
		}
		return pivot;
	}
	static void quickSort(int a[], int l, int r) {
		if (l>=r) return;
		int pivot = rand.nextInt(r-l)+l;
		int p = partition(a, l, r, pivot);
		quickSort(a, l, p-1);
		quickSort(a, p+1, r);
	}
    public static void main(String[] args){
        Scanner scan = new Scanner(System.in);
        rand = new Random();
        int N = scan.nextInt();
        int[] a = new int[N];
        for (int i = 0; i < N; ++i) a[i] = scan.nextInt();
        quickSort(a, 0, a.length-1);
        int min = 1000000000;
        for (int i = 0; i < N-1; i++) {
		    if (a[i+1]-a[i] < min) min = a[i+1]-a[i];
	    }
	    System.out.println(min);
    }
}