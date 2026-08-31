int* nodesBetweenCriticalPoints(struct ListNode* head, int* returnSize) {
    int* ans = (int*)malloc(2 * sizeof(int));
    *returnSize = 2;

    ans[0] = -1;
    ans[1] = -1;

    struct ListNode* prev = head;
    struct ListNode* curr = head->next;

    int pos = 1;
    int first = -1;
    int last = -1;
    int minDist = 1000000000;

    while (curr->next != NULL) {
        struct ListNode* next = curr->next;

     
        if ((curr->val > prev->val && curr->val > next->val) ||
            (curr->val < prev->val && curr->val < next->val)) {

            
            if (first == -1) {
                first = pos;
            }

         
            if (last != -1) {
                int dist = pos - last;

                if (dist < minDist) {
                    minDist = dist;
                }
            }

            last = pos;
        }

        prev = curr;
        curr = next;
        pos++;
    }

    if (first != -1 && first != last) {
        ans[0] = minDist;
        ans[1] = last - first;
    }

    return ans;
}