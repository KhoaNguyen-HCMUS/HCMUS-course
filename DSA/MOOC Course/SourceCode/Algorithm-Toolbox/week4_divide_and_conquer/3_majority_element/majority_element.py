def majority_element_naive(elements):
    candidate = None
    count = 0

    # Phase 1: Find a candidate
    for e in elements:
        if count == 0:
            candidate = e
        count += 1 if e == candidate else -1

    # Phase 2: Verify the candidate
    if elements.count(candidate) > len(elements) / 2:
        return 1
    else:
        return 0


if __name__ == "__main__":
    input_n = int(input())
    input_elements = list(map(int, input().split()))
    assert len(input_elements) == input_n
    print(majority_element_naive(input_elements))
