# Technical Specification

- **Title:** Proactor — Design Documentation
- **Author:** Jake Yoo
- **Date:** 2026-01-25
- **Version:** 0.1
- **Status:** Draft

## 1. Summary
- Create a design document for the specific part of the framework that applies the "Asynchronous Completion Toke" pattern, along with an example application to demonstrate it.

## 2. Goals & Non-Goals
- **Goals:**
  - Document the Asynchronous Completion Token design pattern implementation.
  - Describe the example application, which is implemented based on Proactive framework, from the "Asynchronous Completion Token" design point of view. 
  - Provide an overview of the architectural layout, including:
    - Class diagrams
    - Flow sequences
    - All diagrams should be written in Mermaid diagram format.
- **Non Goals**
  - the deisng document from the view of the Proactor design pattern is already written the below document. Proactor related design doesn't need to be added in the document.   
      - <workspace>/docs/design/ARCH_Proactor_framework_and_application.md 

## 3. Context and Background
- To deepen knowledge of design patterns, I am implementing a simplified version of a framework and an example application to demonstrate the implemented framework.
- The part of the framework applying the Proactor pattern and Asynchronous Completion Token" pattern and the example application for demonstration have been implemented.
- It is required to create a design document for the implemented framework and example application.
- The design document will be used as a reference for writing technical blog posts, such as:
    - https://yjung93.github.io/design%20pattern%20-%20ace%20framework/post-active-object/
    - https://yjung93.github.io/design%20pattern%20-%20ace%20framework/post-halfsync-halfasync/
    - https://yjung93.github.io/design%20pattern%20-%20ace%20framework/post-acceptor-connector/
    - https://yjung93.github.io/design%20pattern%20-%20ace%20framework/post-reactor/

## 4. Reference
- **Source Code:** : the implementation the desing document will be writen for.
  - Proactor Framework (implemented in Proactor pattern and Asynchronous Completion Token pattern):
    - <workspace>/framework/proactor/1_0/*
  - Example Application:
    - applications/example_proactor/*
