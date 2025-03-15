void relu(matrix *m) {
    for (int i = 0; i < m->rows; i++) {
        if (m->data[i] < 0) {
            m->data[i] = 0;
        }
    }
}
