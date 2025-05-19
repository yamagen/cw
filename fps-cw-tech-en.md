# Frequency-based PCA Semantic ID (FPS-ID): A Lightweight Semantic Labeling System for Classical Japanese Corpora

## ✅ Objective

Traditional systems like `wlsp` relied on manually crafted semantic labels and symbolic identifiers, which are unsustainable for scalable and structurally consistent analysis. In classical Japanese corpora (e.g., _Ise Monogatari_, _Tosa Nikki_, and _Kokin Wakashū_), the total number of words is too small for modern word embedding models like fastText to be effective.

To solve this, we introduce **FPS-ID (Frequency-based PCA Semantic ID)**: a compact, interpretable semantic identifier generated from **cooccurrence-based word vectors** compressed via PCA. The digit precision of the resulting ID encodes semantic granularity, enabling human-readable, meaning-ordered labeling.

---

## ✅ Overall Workflow

```sh
% fsp input.txt | cw -k "fps-id" -digit 6 | graphviz -Tsvg -o output.svg
```

| Step       | Description                                                                                                                                                            |
| ---------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `fsp`      | Reads classical Japanese text line-by-line, constructs cooccurrence vectors per word, applies PCA, and outputs 1-word-per-line `streamtext.jsonl` with `fps-id` fields |
| `cw`       | Groups words by the prefix of `fps-id` (as specified by `-digit`) and computes cooccurrence weight: `cw(t1, t2) = ctf × √(idf₁ × idf₂)`                                |
| `graphviz` | Visualizes the weighted graph to reveal semantically coherent clusters                                                                                                 |

---

## ✅ FPS-ID Specification

### Structure:

- Source: **Word cooccurrence matrix** derived from classical texts
- Compression: PCA (typically 1D or 2D)
- Output: Floating-point string such as `"fps-id": "23.614729"`

### Semantic Granularity by Digits:

| Digits       | Meaning                                          | Use Case                                      |
| ------------ | ------------------------------------------------ | --------------------------------------------- |
| `23`         | Coarse semantic cluster (e.g., seasons, animals) | Filtering, high-level classification          |
| `23.61`      | Synonym group (e.g., 春 vs 秋)                   | Grouped display, sorting                      |
| `23.6147...` | Fine-grained contextual variants                 | Sense disambiguation, poetic nuance detection |

---

## ✅ Example Entry in `streamtext.jsonl`

```json
{
  "form": "春",
  "lemma": "春",
  "pos": "NOUN",
  "fps-id": "23.48",
  "line": 12,
  "token_index": 3
}
```

---

## ✅ cw Integration (Cooccurrence Weighting)

### Functionality

- Input: `streamtext.jsonl`
- Key option: `-k fps-id`
- Digit precision: `-digit 6` → groups words by the first 6 digits of `fps-id`
- Output: `fps-id1 fps-id2 weight`

### Weight Formula

```math
cw(t1, t2) = ctf × √(idf₁ × idf₂)
```

---

## ✅ Advantages

### For Classical Corpora

- ✅ No need for large training data or fastText-style embeddings
- ✅ Entirely self-contained: uses the corpus itself as semantic evidence
- ✅ Works with 10k–50k token corpora (Ise, Tosa, Kokin, etc.)

### Interpretability

- ✅ Human-readable, sortable semantic IDs
- ✅ Control abstraction via digit truncation
- ✅ Transparent structure: no hidden neural layers

### Visual Semantics

- ✅ Graph structure reveals poetic or rhetorical groupings
- ✅ Use of `graphviz` allows immediate inspection of results

---

## ✅ Future Directions

- Develop `kfps` toolkit: word cooccurrence → PCA → fps-id encoder
- Support inverse mapping table (`fpsid2text.tsv`)
- Build `fpsid-cluster-browser`: a GUI for visually navigating semantic clusters
- Compare with handcrafted `wlsp` labels for interpretive studies

---

> **FPS-ID = Frequency-based PCA Semantic ID**
> A lightweight, interpretable, corpus-driven semantic ID system ideal for small-scale poetic and classical language analysis.

---
