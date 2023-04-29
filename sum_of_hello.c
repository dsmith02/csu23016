#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 6
#define USERNAME "username"

// https://learn-eu-central-1-prod-fleet01-xythos.content.blackboardcdn.com/62b985ffa0afc/4940466?X-Blackboard-S3-Bucket=learn-eu-central-1-prod-fleet01-xythos&X-Blackboard-Expiration=1675047600000&X-Blackboard-Signature=q188Sky3BB6AfgHSAH6a%2BcdODIN%2BQoj%2BZ84n9PGjmWo%3D&X-Blackboard-Client-Id=300200&X-Blackboard-S3-Region=eu-central-1&response-cache-control=private%2C%20max-age%3D21600&response-content-disposition=inline%3B%20filename%2A%3DUTF-8%27%27SumOfHellos.pdf&response-content-type=application%2Fpdf&X-Amz-Security-Token=IQoJb3JpZ2luX2VjEAYaDGV1LWNlbnRyYWwtMSJHMEUCIC9%2BS%2F5hpIJeT5M70kRUcgMpvODxhRKwktuSmug6KuYAAiEAoz928H9M%2FYfBwAlWXWnawPvKBC0qs%2BNIpoeqf%2BaPS8IqvgUIfxACGgw2MzU1Njc5MjQxODMiDPgsmoR3UYGvCrJsySqbBfj59xoUrncZis%2FRnIOqowPWRFwrvKgVoS09CUP2B9%2FmKSUS3TLno6DKZWpKh2HgL5l%2BFsMw9zu4%2Bz57aVs1t%2BXiR6DeNeytdTi3qWDfqkd7Wjbt%2B8HH0gvrnIZXyMHyv1NAH6DVjBk8%2B1UbhB25o3aeHXizt5PwiYVK3anBeVMKG9TTBHYbM0Vl7LJBWoKq1uI1zsxJabMty750L7otS0DgYYaxpTID8v%2FNF%2FwtL9t4aYEEnbXv%2BZnUeWDrQkH8QbTbSjqLJsoBtun0k8vSXlrMMAjbp4y%2FEGfnnQF4VAvnSB5zWnM9JYNAVQNZfeCIyxz5y9JoPq0JjGaKpZ1kxoyDl2gzPILQ%2FNYgUUcRmgtnGnE3Iz7ayDHE6IRS886HjqmVm2PfhzBAHP31ZyGj1CVu6xLPk6sLuxqDiSStKPLNayGG53bCkFqYdSWXCWeghzCC9pUqY6e8pj%2BOa%2FMK1fUR5iwwV%2BdHqEfFbTCCy%2FSyFst2uvIrv47zwHnLWosKOhnP3InvUxx1FlDeHlFy1s0uTx74%2FWOxzC%2BjRzAMTOQ0hWZvYXxgGlT%2BZFMtSWBMG6NZc68XYtAS6OuWXmYOVcPpvql2cHHcR%2Fz%2F%2FmhmqtA3kRwgdpLfF8vVCJrjWab9EwbDdzF8R8%2BL7%2BwoZV6jYNhZgRu56pHe8xMEpbzcL439b8Sk%2FFXBcDu5U4p2N4RttZE05JvyVp0Aa2wNfhUQdci3LK8PQCompwj7TkmirQojiVMM61izfqSApoh2hy4FCaj8CTpYhi3pXSLtRCw0l9PDGNbGTL%2B5rN5lAH4s4uujfBa%2Fo89dm%2FFh2MVo0Ez%2BuUuHa58J8obWBdqRIH9bDhd3Ybbn1fBIGMWu%2F2y7fJHdHiJtKNMlqSFVG9QwrsrbngY6sQFWtmVrdN1QMeEaHwk9DCGaJDfE1XRoZlS%2BqYxevrXjZYM3aUjCgbghd8sJEBIh9mKfUX2t36NDR5jP6WdMrpRf6XD83wJz0H557o0f%2FmR7Q6YdhDA6AjWUsEKNzwUtKU%2FcO93RwMlMXmDkHEpVkmQfRadQw7FXnvNIfYcIwC6W0iX1nEAlnJz7TL9OlTIxWiiBSeNPE%2BzqQkg1uszHHz%2FAnBsrFUVaxvfS2IruiPJMfCM%3D&X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Date=20230129T210000Z&X-Amz-SignedHeaders=host&X-Amz-Expires=21600&X-Amz-Credential=ASIAZH6WM4PLQHMMAB5H%2F20230129%2Feu-central-1%2Fs3%2Faws4_request&X-Amz-Signature=8f4b33c811afdea4e15bcde43d0faa2581bd991755c8ae13c05df60d2227ae91


int x; // global variable

void *PrintHello(void *threadid)
{
    int y; // (Thread) local variable

    y = x; // read global var
    printf("\n%d: Hello World, from %s!\n", threadid, USERNAME);
    x = y + 1; // write to global var
    pthread_exit(NULL);
}

int main(int argc, const char *argv[])
{
    pthread_t threads[NUM_THREADS];
    int rc, t;
    x = 0; // initialise global
    for (t = 0; t < NUM_THREADS; t++)
    {
        printf("Creating thread %d\n", t);
        rc = pthread_create(&threads[t], NULL, PrintHello, (void *)t);
        if (rc)
        {
            printf("ERROR return code from pthread_create(): %d\n", rc);
            exit(-1);
        }
    }
    for (t = 0; t < NUM_THREADS; t++)
    {
        pthread_join(threads[t], NULL);
    }
    printf("\nAll threads done by %s, x = %d\n", USERNAME, x);
    return 0;
}