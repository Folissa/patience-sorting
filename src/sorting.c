int merge() {
    // 
}

void distribute() {
    //
}

void sort() {
    int sorted = 0;

    while (!sorted) {
        distribute();
        sorted = merge();
    }
}