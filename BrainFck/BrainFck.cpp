#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct BFState {
    size_t array_len;
    vector<uint8_t> array{};
    vector<uint8_t>::iterator cur = array.begin();
};

int brainfuck(BFState* state, const string& program) {
    vector<size_t> stack;
    size_t stack_pos = 0;

    state->array.resize(state->array_len, 0);

    for (auto pc = program.begin(); pc != program.end(); ++pc) {
        switch (*pc) {
        case '>':
            if (state->cur + 1 >= state->array.end()) {
                return -1;
            }
            ++state->cur;
            break;

        case '<':
            if (state->cur <= state->array.begin()) {
                return -1;
            }
            --state->cur;
            break;

        case '+':
            ++(*state->cur);
            break;

        case '-':
            --(*state->cur);
            break;

        case '[':
            if (*state->cur == 0) {
                auto it = find(pc + 1, program.end(), ']');
                if (it == program.end()) {
                    return -1;
                }
                pc = it;
            }
            else {
                stack.push_back(pc - program.begin());
            }
            break;

        case ']':
            if (*state->cur != 0) {
                pc = program.begin() + stack.back() - 1;
            }
            else {
                stack.pop_back();
            }
            break;

        default:
            break;
        }
    }
    return 0;
}

int main() {
    BFState* obj1 = new BFState();
    const string rhs{ "das<>><[]][\0" };
    brainfuck(obj1, rhs);
}
