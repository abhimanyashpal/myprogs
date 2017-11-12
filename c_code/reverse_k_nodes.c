/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

void reverse_sub (struct ListNode **head, struct ListNode **start, struct ListNode **end)
{
    struct ListNode *curr, *curr_end,*next;
    struct ListNode *new_head, *prev = NULL;

    if (!start || !end)
         return;

    curr = *start;
    curr_end  = *end;


    while (curr != curr_end)
    {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    //Edge case
    curr->next = prev;
    prev = curr;

    *end = *start;
    *start = prev;

     //printf("\n SUB end :: %d", (*end)->val);
     //printf("\n SUB start :: %d", prev->val);
}

int
reverse_helper (struct ListNode **head, struct ListNode **next_sub, struct ListNode **prev, int k)
{
    struct ListNode *curr_start, *curr_end, *p2;
    int t = k;

    curr_start = *head;
    p2 = curr_start;

    while (t > 0) {

        if (!p2) {
            return -1;
        }

        curr_end = p2;
        p2 = p2->next;
        t--;
    }

    #if 0
    printf("\nP2 :: %d",p2->val);
    printf("\ncurr_s :: %d",curr_start->val);
    printf("\ncurr_e :: %d",curr_end->val);
    #endif

    reverse_sub(head, &curr_start, &curr_end);

    printf("\ncurr_s :: %d",curr_start->val);
    printf("\ncurr_e :: %d",curr_end->val);

    if (!(*prev)) {
        *head = curr_start;
   // printf("\n orig_head2:: %llu %d",(unsigned long long)(*head), (*head)->val);
    } else {
         (*prev)->next = curr_start;
    }

    curr_end->next = p2;

    *prev = curr_end; //End of the previous sub-list
    *next_sub = p2;

    return 0;
}

struct ListNode* reverse(struct ListNode **head, int k)
{
    struct ListNode *next_sub_head = NULL, *prev_sub_end = NULL;
    int ret_val = 0;
    struct ListNode **wrk_head;


    if (!head)
         return NULL;

    if (!(*head))
          return NULL;
    
     if (k < 2)
        return *head;

    //printf("\n orig_head:: %llu",(unsigned long long)(*head));

    wrk_head = head;
    while (1)
    {
        ret_val = reverse_helper(wrk_head, &next_sub_head, &prev_sub_end, k);

        #if 0
        if (next_sub_head) {
            printf("\nNext head:: %d",next_sub_head->val);
        }
        if (prev_sub_end) {
            printf("\nPrev end:: %d", prev_sub_end->val);
        }
        #endif
        
        wrk_head = &next_sub_head;

        if (ret_val < 0)
             break;
    }

    printf("\n head :: %u",(*head)->val);
    
    return *head;
}



struct ListNode* reverseKGroup(struct ListNode* head, int k) {
    
    if (!head)
        return NULL;
    
    return reverse(&head, k);
    
}
