// bwt-search is to implement O(N) search for compressed data without decoding the whole file.

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>

#define CHAR_NUM 96
#define INDEX_BLOCK_SIZE (CHAR_NUM * sizeof(unsigned int))
#define BWT_BLOCK_SIZE (1024 * sizeof(unsigned int))

using namespace std;

static unsigned int chr_map[127] = {0};
static unsigned int C[CHAR_NUM] = {0};

unsigned int gen_occ_index_file(istream &in, ofstream &index_out) {
    in.clear();
    index_out.clear();
    in.seekg(0, ios_base::beg);

    unsigned int index_array[CHAR_NUM] = {0};
    unsigned int blocks = 0;
    char buf[BWT_BLOCK_SIZE] = {0};
    while (true) {
        in.read(buf, BWT_BLOCK_SIZE);
        if (in.gcount() == BWT_BLOCK_SIZE) {
            for (char i : buf)
                index_array[chr_map[i]]++;
            index_out.write((char *) index_array, INDEX_BLOCK_SIZE);
            blocks++;
        } else
            break;
    }
    return blocks;
}

void gen_chr_map() {
    chr_map[10] = 0;
    for (int i = 32; i <= 126; i++) {
        chr_map[i] = i - 31;
    }
}

void gen_C_table(istream &in, istream &index_in, unsigned int blocks) {
    in.clear();
    index_in.clear();

    if (blocks > 0) {
        index_in.seekg(-INDEX_BLOCK_SIZE, ios_base::end);
        index_in.read((char *) C, INDEX_BLOCK_SIZE);
    }

    in.seekg(blocks * BWT_BLOCK_SIZE, ios_base::beg);

    char c;
    while (in.get(c)) {
        C[chr_map[c]]++;
    }

    for (int i = 1; i < CHAR_NUM; i++) {
        C[i] += C[i - 1];
    }
}

unsigned int get_C(unsigned char symbol) {
    if (symbol + 1 == '\n')
        return 0;
    return C[chr_map[symbol]];
}

unsigned int get_occ(unsigned char symbol, unsigned int pos, istream &in, istream &index_in) {
    in.clear();
    index_in.clear();

    unsigned int pos_blocks = pos / BWT_BLOCK_SIZE;
    unsigned int c_index = chr_map[symbol];
    unsigned int num_match = 0;

    if (pos_blocks > 0) {
        unsigned int offset = (pos_blocks - 1) * INDEX_BLOCK_SIZE + c_index * sizeof(unsigned int);
        index_in.seekg(offset, ios_base::beg);
        index_in.read((char *) &num_match, sizeof(unsigned int));
    }

    in.seekg(pos_blocks * BWT_BLOCK_SIZE, ios_base::beg);

    unsigned int count = pos_blocks * BWT_BLOCK_SIZE;
    char c;

    while (count < pos && in.get(c)) {
        if (c == symbol) {
            num_match++;
        }
        count++;
    }
    return num_match;
}

bool bwt_search(const char *pattern, ifstream &in, ifstream &index_in, unsigned int &F, unsigned int &L) {
    in.clear();
    index_in.clear();

    unsigned int len = strlen(pattern);
    char c = pattern[len - 1];

    F = get_C(c - 1);
    L = get_C(c) - 1;


    for (int i = (int) len - 2; i >= 0; i--) {
        if (F > L)
            return false;
        c = pattern[i];
        F = get_C(c - 1) + get_occ(c, F, in, index_in);
        L = get_C(c - 1) + get_occ(c, L + 1, in, index_in) - 1;
    }

    return true;
}

void read_lines(ifstream &in, ifstream &index_in, unsigned int F, unsigned int L, vector<int> &line_indexes) {
    in.clear();
    index_in.clear();

    char c;
    unsigned int next;
    for (int i = (int) F; i <= L; i++) {
        string line;
        in.seekg(i, ios_base::beg);
        in.get(c);
        next = get_occ(c, i, in, index_in) + get_C(c - 1);
        while (c != '\n') {
            in.seekg(next, ios_base::beg);
            in.get(c);
            next = get_occ(c, next, in, index_in) + get_C(c - 1);
            if (c != '\n')
                line.insert(0, string(1, c));
        }
        line = line.substr(0, line.find(' '));
        line_indexes.push_back(stoi(line));
    }
}

void decode(ifstream &in, ifstream &index_in, ofstream &decode_out) {
    in.clear();
    index_in.clear();

    char c;
    unsigned int next;

    for (int i = 1; i <= get_C('\n'); i++) {
        if (i == get_C('\n'))
            i = 0;
        string line = "\n";
        in.seekg(i, ios_base::beg);
        in.get(c);
        line.insert(0, string(1, c));
        next = get_occ(c, i, in, index_in) + get_C(c - 1);
        while (true) {
            in.seekg(next, ios_base::beg);
            in.get(c);
            next = get_occ(c, next, in, index_in) + get_C(c - 1);
            if (c == '\n')
                break;
            line.insert(0, string(1, c));
        }
        decode_out << line;
        if (i == 0)
            break;
    }
}

void output_records(ifstream &in, ifstream &index_in, const vector<int> &line_indexes) {
    in.clear();
    index_in.clear();

    char c;
    unsigned int next;

    for (int i : line_indexes) {
        if (i == get_C('\n')) {
            i = 0;
        }
        string line = "\n";
        in.seekg(i, ios_base::beg);
        in.get(c);
        line.insert(0, string(1, c));
        next = get_occ(c, i, in, index_in) + get_C(c - 1);
        while (true) {
            in.seekg(next, ios_base::beg);
            in.get(c);
            next = get_occ(c, next, in, index_in) + get_C(c - 1);
            if (c == '\n')
                break;
            line.insert(0, string(1, c));
        }
        cout << line;
    }
}

void output(const char *flag, ifstream &in, ifstream &index_in, unsigned int F, unsigned int L) {
    vector<int> line_indexes;
    read_lines(in, index_in, F, L, line_indexes);

    if (!strcmp(flag, "")) {
        sort(line_indexes.begin(), line_indexes.end());
        auto last = std::unique(line_indexes.begin(), line_indexes.end());
        line_indexes.erase(last, line_indexes.end());
        output_records(in, index_in, line_indexes);
    } else if (!strcmp(flag, "-m")) {
        cout << line_indexes.size() << endl;
    } else if (!strcmp(flag, "-n")) {
        sort(line_indexes.begin(), line_indexes.end());
        auto last = std::unique(line_indexes.begin(), line_indexes.end());
        line_indexes.erase(last, line_indexes.end());
        cout << line_indexes.size() << endl;
    }
}


int main(int argc, char *argv[]) {
    const char *bwt_file;
    const char *index_file;
    const char *decode_file = "decode";
    const char *pattern;
    const char *flag;
    unsigned int blocks;
    unsigned int F, L;

    if (argc < 4 || argc > 6) {
        cerr << "bwtsearch (-m|-n|-o|) bwt idx pattern";
        return -1;
    } else if (argc == 4) {
        flag = "";
        bwt_file = argv[1];
        index_file = argv[2];
        pattern = argv[3];
    } else {
        flag = argv[1];
        if (!strcmp(flag, "-o")) {
            bwt_file = argv[2];
            index_file = argv[3];
            decode_file = argv[4];

        } else {
            bwt_file = argv[2];
            index_file = argv[3];
            pattern = argv[4];
        }
    }

    ifstream in(bwt_file);
    ifstream index_in(index_file, ifstream::binary);
    ofstream decode_out(decode_file);

    gen_chr_map();

    if (!index_in.good()) {
        index_in.close();
        ofstream index_out(index_file, std::ofstream::trunc | ofstream::binary);
        gen_occ_index_file(in, index_out);
        index_out.close();
    }
    index_in.open(index_file, ifstream::binary);
    index_in.seekg(0, ios_base::end);
    int index_size = index_in.tellg();
    if (index_size == -1) {
        blocks = 0;
    } else {
        blocks = index_in.tellg() / INDEX_BLOCK_SIZE;
    }
    index_in.seekg(0, ios_base::beg);
    gen_C_table(in, index_in, blocks);

    if (!strcmp(flag, "-o")) {
        decode(in, index_in, decode_out);
        in.close();
        index_in.close();
        decode_out.close();
        return 0;
    }

    bool result = bwt_search(pattern, in, index_in, F, L);
    if (result)
        output(flag, in, index_in, F, L);

    in.close();
    index_in.close();
    decode_out.close();
    return 0;
}
