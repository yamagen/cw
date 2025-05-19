# From WLSP Codes to Stance-Triple DAG: Structural Reform for Semantic Representation

## Overview: Current WLSP Code System and Its Implementation

The "WLSP (Word List with Semantic Properties)" project (e.g., [WLSP on GitHub](https://github.com/masayu-a/WLSP)) is a structured system for classifying Japanese vocabulary with hierarchical and functionally rich codes. Each code includes semantic and syntactic information, such as:

```
WLSP:BG-01-1630-01-0100 → 年 (toki / nen / toshi)
WLSP:BG-01-1911-03-1800 → 年 (measure / duration)
WLSP:BG-08-0061-07-0100 → の (genitive particle)
```

In annotated corpora, these codes are attached to each token as shown:

```
01:000001:0001 A00 WLSP:BG-01-1630-01-0100 年
01:000001:0001 A10 WLSP:BG-01-1911-03-1800 年
01:000001:0002 A00 WLSP:BG-08-0061-07-0100 の
```

### Intended Strengths

- Hierarchical structure allows deep semantic classification.
- Unified syntax-semantic indexing for dictionary building and annotation.
- Extensively curated for Japanese lexicography and corpus linguistics.

## Critical Weaknesses of the WLSP/BG System

1. **Code Semantics Are Not Human-Transparent**
   → `WLSP:BG-01-1630-01-0100` does not directly express "temporal-recurrent meaning" to human readers or algorithms.

2. **Rigidity and Overclassification**
   → The structure requires extensive code consistency; reclassification is difficult.

3. **Multiple Entries for One Surface Word**
   → e.g., 年 is annotated with both "time-point" and "duration" codes, with no guiding logic for disambiguation.

4. **Number-Based Hierarchy Not Optimal for NLP Semantics**
   → Systems like vector embeddings, typological mapping, or pragmatics modeling require a different level of abstraction.

5. **No Representation of Discourse-Level or Stance-Level Meaning**
   → Words like けり or は perform rhetorical, modal, or affective functions—unaddressed in BG codes.

---

## Reform Proposal: DAG Based on Stance-Triple Theory

We propose replacing the rigid code hierarchy with a **Directed Acyclic Graph (DAG)** model based on a minimal triplet:

```
stance-triple = (category, stance, lemma)
```

Each DAG node represents an interpretable unit anchored in discourse-pragmatic behavior.

### Example Conversion

Original:

```
01:000001:0001 A00 WLSP:BG-01-1630-01-0100 年
01:000001:0001 A10 WLSP:BG-01-1911-03-1800 年
```

Converted to stance-triple DAG:

```json
{
  "category": "temporal-measurement",
  "stance": "objective-reference",
  "lemma": "年"
},
{
  "category": "temporal-recurrence",
  "stance": "cyclical-awareness",
  "lemma": "年"
}
```

Other examples:

```json
{
  "category": "grammatical-particle",
  "stance": "possessive-link",
  "lemma": "の"
},
{
  "category": "season",
  "stance": "sensory-invocation",
  "lemma": "春"
},
{
  "category": "aspect",
  "stance": "perfective-certainty",
  "lemma": "ぬ"
},
{
  "category": "modality",
  "stance": "evidential-retrospective",
  "lemma": "けり"
}
```

---

## Advantages of the Stance-Triple DAG System

- 🌱 **Conceptually transparent and linguistically structured**
- 🧩 **Non-fragile extensibility**: Stance or category sets can evolve independently.
- 🔍 **Encodes discourse sensitivity**: Multiple readings of 年 can coexist in DAG without conflict.
- 🌐 **Cross-linguistic transferability**: Shared stance-category schemas can support multilingual projects.
- 🤖 **Compatible with semantic vector models**: Use as labels or interpretive scaffolding.

---

## Conclusion

While the WLSP-based BG code system remains valuable for lexicographic classification, it lacks flexibility and explicit pragmatic encoding. The stance-triple DAG approach offers a human-readable, computationally robust framework that accounts for meaning, function, and discourse positioning.

This transition moves from a static taxonomic schema to a **dynamic semantic-pragmatic model**, better suited to capturing the richness and elliptical expressiveness of classical texts such as waka.
