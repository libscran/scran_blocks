<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile doxygen_version="1.9.8">
  <compound kind="file">
    <name>average_vectors.hpp</name>
    <path>scran/</path>
    <filename>average__vectors_8hpp.html</filename>
    <namespace>scran</namespace>
    <namespace>scran::average_vectors</namespace>
  </compound>
  <compound kind="file">
    <name>block_weights.hpp</name>
    <path>scran/</path>
    <filename>block__weights_8hpp.html</filename>
    <class kind="struct">scran::block_weights::VariableParameters</class>
    <namespace>scran</namespace>
    <namespace>scran::block_weights</namespace>
  </compound>
  <compound kind="file">
    <name>scran.hpp</name>
    <path>scran/</path>
    <filename>scran_8hpp.html</filename>
    <namespace>scran</namespace>
  </compound>
  <compound kind="struct">
    <name>scran::block_weights::VariableParameters</name>
    <filename>structscran_1_1block__weights_1_1VariableParameters.html</filename>
    <member kind="variable">
      <type>double</type>
      <name>lower_bound</name>
      <anchorfile>structscran_1_1block__weights_1_1VariableParameters.html</anchorfile>
      <anchor>a79fe089ceefdb0ccf951c123e744fd9d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>upper_bound</name>
      <anchorfile>structscran_1_1block__weights_1_1VariableParameters.html</anchorfile>
      <anchor>ac9ead8e533b758d8f7eea424ecc91e1b</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>scran</name>
    <filename>namespacescran.html</filename>
    <namespace>scran::average_vectors</namespace>
    <namespace>scran::block_weights</namespace>
  </compound>
  <compound kind="namespace">
    <name>scran::average_vectors</name>
    <filename>namespacescran_1_1average__vectors.html</filename>
    <member kind="function">
      <type>void</type>
      <name>compute</name>
      <anchorfile>namespacescran_1_1average__vectors.html</anchorfile>
      <anchor>a4e172bae14695de308541d81cc138ea0</anchor>
      <arglist>(size_t n, std::vector&lt; Stat_ * &gt; in, Output_ *out, bool skip_nan)</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; Output_ &gt;</type>
      <name>compute</name>
      <anchorfile>namespacescran_1_1average__vectors.html</anchorfile>
      <anchor>af7d67ef4b70d6e0eb782b69448155c7c</anchor>
      <arglist>(size_t n, std::vector&lt; Stat_ * &gt; in, bool skip_nan)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>compute_weighted</name>
      <anchorfile>namespacescran_1_1average__vectors.html</anchorfile>
      <anchor>aeceb59d0faa34d55113e9d10f1b60490</anchor>
      <arglist>(size_t n, std::vector&lt; Stat_ * &gt; in, const Weight_ *w, Output_ *out, bool skip_nan)</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; Output_ &gt;</type>
      <name>compute_weighted</name>
      <anchorfile>namespacescran_1_1average__vectors.html</anchorfile>
      <anchor>ac8147a5bc1b37991997de58c1a4f1752</anchor>
      <arglist>(size_t n, std::vector&lt; Stat_ * &gt; in, const Weight_ *w, bool skip_nan)</arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>scran::block_weights</name>
    <filename>namespacescran_1_1block__weights.html</filename>
    <class kind="struct">scran::block_weights::VariableParameters</class>
    <member kind="enumeration">
      <type></type>
      <name>Policy</name>
      <anchorfile>namespacescran_1_1block__weights.html</anchorfile>
      <anchor>aa73ad0ce9a2905611bb940a210323bf7</anchor>
      <arglist></arglist>
      <enumvalue file="namespacescran_1_1block__weights.html" anchor="aa73ad0ce9a2905611bb940a210323bf7ab50339a10e1de285ac99d4c3990b8693">NONE</enumvalue>
      <enumvalue file="namespacescran_1_1block__weights.html" anchor="aa73ad0ce9a2905611bb940a210323bf7ae61ad9b2553a293b4a3f4d3b4fa5ab31">VARIABLE</enumvalue>
      <enumvalue file="namespacescran_1_1block__weights.html" anchor="aa73ad0ce9a2905611bb940a210323bf7a969f331a87d8c958473c32b4d0e61a44">EQUAL</enumvalue>
    </member>
    <member kind="function">
      <type>double</type>
      <name>compute_variable</name>
      <anchorfile>namespacescran_1_1block__weights.html</anchorfile>
      <anchor>a87cc462ecac05cd391007c5b1dd77cfc</anchor>
      <arglist>(double s, const VariableParameters &amp;params)</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; double &gt;</type>
      <name>compute</name>
      <anchorfile>namespacescran_1_1block__weights.html</anchorfile>
      <anchor>a1a9e797af79dad83d063605d50b7099e</anchor>
      <arglist>(const std::vector&lt; Size_ &gt; &amp;sizes, Policy policy, const VariableParameters &amp;variable)</arglist>
    </member>
  </compound>
  <compound kind="page">
    <name>index</name>
    <title>Utilities for scran</title>
    <filename>index.html</filename>
    <docanchor file="index.html" title="Utilities for scran">md__2github_2workspace_2README</docanchor>
  </compound>
</tagfile>
