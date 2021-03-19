import java.util.Scanner;
import java.lang.Math;
import java.util.Random;

/**
 * Matt Crow
*/
public class AVLTreeNode {
    private int priority;
    private AVLTreeNode left;
    private AVLTreeNode right;
    private int height;

    private AVLTreeNode(int priority){
        this.priority = priority;
        this.left = null;
        this.right = null;
        this.height = 0;
    }

    private static void updateHeight(AVLTreeNode root){
        if(root != null){
            root.height = Math.max(
                getHeight(root.left),
                getHeight(root.right)
            ) + 1;
        }
    }

    /*
    Retrieves cached height for initialized nodes,
    and -1 for null pointers
    */
    private static int getHeight(AVLTreeNode root){
        int height = -1;
        if(root != null){
            height = root.height;
        }
        return height;
    }

    public static AVLTreeNode findMin(AVLTreeNode root){
        AVLTreeNode lefternMost = root;
        if(lefternMost != null && lefternMost.left != null){
            lefternMost = findMin(root.left);
        }
        return lefternMost;
    }

    private static int getBalance(AVLTreeNode root){
        int balance = 0;
        if(root != null){
            balance = getHeight(root.left) - getHeight(root.right);
        }
        return balance;
    }

    private static AVLTreeNode rebalance(AVLTreeNode root){
        AVLTreeNode newRoot = root;
        if(root != null){
            updateHeight(newRoot); // it's height may have changed by 1
            // the height of its children have already been updated,
            // as the recursion travels upward.
            int rootBal = getBalance(newRoot);
            if(rootBal < -1){ // right heavy
                if(getBalance(newRoot.right) > 1){
                    // right heavy inner
                    newRoot.right = rotateRight(newRoot.right);
                }
                newRoot = rotateLeft(newRoot);
            } else if(rootBal > 1){ // left heavy
                if(getBalance(newRoot.left) < -1){
                    // left heavy inner
                    newRoot.left = rotateLeft(newRoot.left);
                }
                newRoot = rotateRight(newRoot);
            }
        }
        return newRoot;
    }

    /*
         (4)
        /   \
      (2)    (6)
     /  \    /  \
    (1) (3) (5) (7)

    rotateLeft((4)):
            (6)
           /   \
         (4)   (7)
        /   \
      (2)   (5)
     /   \
    (1)  (3)
    */
    private static AVLTreeNode rotateLeft(AVLTreeNode root){
        AVLTreeNode newRoot = null;
        if(root != null){
            newRoot = root.right;
            root.right = newRoot.left;
            newRoot.left = root;
            updateHeight(root);
            updateHeight(newRoot);
        }
        return newRoot;
    }

    /*
         (4)
        /   \
      (2)    (6)
     /  \    /  \
    (1) (3) (5) (7)

    rotateRight((4)):
        (2)
       /   \
      (1)  (4)
           /  \
         (3)  (6)
              /  \
            (5)  (7)
    */
    private static AVLTreeNode rotateRight(AVLTreeNode root){
        AVLTreeNode newRoot = null;
        if(root != null){
            newRoot = root.left;
            root.left = newRoot.right;
            newRoot.right = root;
            updateHeight(root);
            updateHeight(newRoot);
        }
        return newRoot;
    }

    public static AVLTreeNode insert(AVLTreeNode root, int priority){
        AVLTreeNode newRoot = root;
        if(root == null){
            newRoot = new AVLTreeNode(priority);
        } else if(newRoot.priority > priority){
            newRoot.left = insert(newRoot.left, priority);
            newRoot = rebalance(newRoot);
        } else if(root.priority < priority){
            newRoot.right = insert(newRoot.right, priority);
            newRoot = rebalance(newRoot);
        } else {
            // duplicate value, do nothing
        }
        return newRoot;
    }

    public static AVLTreeNode remove(AVLTreeNode root, int priority){
        AVLTreeNode newRoot = root;
        if(root == null){
            // do nothing
        } else if(root.priority > priority){
            root.left = remove(root.left, priority);
        } else if(root.priority < priority){
            root.right = remove(root.right, priority);
        } else if(root.left == null && root.right == null){ // found at this point
            newRoot = null;
        } else if(root.left != null && root.right != null){
            // two children
            root.priority = findMin(root.right).priority;
            // swap minimum child from right subtree with root
            root.right = remove(root.right, root.priority); // delete duplicate
        } else if(root.left != null){
            // pull up left child over root
            newRoot = root.left;
        } else if(root.right != null){
            newRoot = root.right;
        } else {
            throw new RuntimeException();
        }
        newRoot = rebalance(newRoot);

        return newRoot;
    }

    /**
     * Creates an array containing the integers 0 <= i < n
     * in a random order
    */
    public static int[] createRandomArray(int n){
        int[] array = new int[n];
        int temp = -1;
        int swapIdx = -1;
        Random rng = new Random();

        // initialize
        for(int i = 0; i < n; i++){
            array[i] = i;
        }

        // randomize
        // https://stackoverflow.com/questions/1519736/random-shuffling-of-an-array
        for(int i = array.length - 1; i > 0; i--){
            swapIdx = rng.nextInt(i + 1);
            temp = array[swapIdx];
            array[swapIdx] = array[i];
            array[i] = temp;
        }

        return array;
    }

    public static void main(String[] args){
        Scanner in = new Scanner(System.in);
        int[] priorities = createRandomArray(5000);
        long startTime;
        long duration;

        AVLTreeNode activeQueue = null;
        AVLTreeNode expiredQueue = null;

        AVLTreeNode min = null;
        int oldPriority;

        String userIp = "";

        // Populate active queue
        for(int priority : priorities){
            activeQueue = insert(activeQueue, priority);
        }

        //System.out.printf("Height of tree is %d\n", getHeight(activeQueue));
        //in.nextLine();


        /*
        Note that the program exits upon entering a non-whitespace character.
        */
        while(userIp.trim().equals("")){
            startTime = System.nanoTime(); // start timer
            while(activeQueue != null){
                min = findMin(activeQueue);
                activeQueue = activeQueue.remove(activeQueue, min.priority);
                System.out.printf("The process with a priority of %d is now scheduled to run!\n", min.priority);
                oldPriority = min.priority;
                min.priority = priorities[min.priority];
                expiredQueue = insert(expiredQueue, min.priority);
                System.out.printf("The process with a priority of %d has run out of its timeslice!\n", oldPriority);
                // Prof. specified in class we are to print old priority, not new one
            }
            duration = System.nanoTime() - startTime; // end timer
            System.out.printf("Completed loop iteration in %d nanoseconds\n", duration);
            System.out.printf("Everyprocess has got a chance to run; Please press \"Enter\" to start the next round! ");
            userIp = in.nextLine();
            if(userIp.trim().equals("")){
                activeQueue = expiredQueue;
                expiredQueue = null;
            }
        }
        in.close();
    }
}
