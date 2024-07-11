<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile doxygen_version="1.9.8">
  <compound kind="file">
    <name>average_vectors.hpp</name>
    <path>scran_blocks/</path>
    <filename>average__vectors_8hpp.html</filename>
    <namespace>scran_blocks</namespace>
  </compound>
  <compound kind="file">
    <name>block_weights.hpp</name>
    <path>scran_blocks/</path>
    <filename>block__weights_8hpp.html</filename>
    <class kind="struct">scran_blocks::VariableWeightParameters</class>
    <namespace>scran_blocks</namespace>
  </compound>
  <compound kind="file">
    <name>scran_blocks.hpp</name>
    <path>scran_blocks/</path>
    <filename>scran__blocks_8hpp.html</filename>
    <namespace>scran_blocks</namespace>
  </compound>
  <compound kind="struct">
    <name>scran_blocks::VariableWeightParameters</name>
    <filename>structscran__blocks_1_1VariableWeightParameters.html</filename>
    <member kind="variable">
      <type>double</type>
      <name>lower_bound</name>
      <anchorfile>structscran__blocks_1_1VariableWeightParameters.html</anchorfile>
      <anchor>a0c21095e5569208fa946c7f1b5791ea5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>upper_bound</name>
      <anchorfile>structscran__blocks_1_1VariableWeightParameters.html</anchorfile>
      <anchor>a865b484b6fc8611048fcadab863de6bf</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>scran_blocks</name>
    <filename>namespacescran__blocks.html</filename>
    <class kind="struct">scran_blocks::VariableWeightParameters</class>
    <member kind="enumeration">
      <type></type>
      <name>WeightPolicy</name>
      <anchorfile>namespacescran__blocks.html</anchorfile>
      <anchor>ac2412948da94055ff438267ba089ba97</anchor>
      <arglist></arglist>
      <enumvalue file="namespacescran__blocks.html" anchor="ac2412948da94055ff438267ba089ba97ab50339a10e1de285ac99d4c3990b8693">NONE</enumvalue>
      <enumvalue file="namespacescran__blocks.html" anchor="ac2412948da94055ff438267ba089ba97ae61ad9b2553a293b4a3f4d3b4fa5ab31">VARIABLE</enumvalue>
      <enumvalue file="namespacescran__blocks.html" anchor="ac2412948da94055ff438267ba089ba97a969f331a87d8c958473c32b4d0e61a44">EQUAL</enumvalue>
    </member>
    <member kind="function">
      <type>void</type>
      <name>average_vectors</name>
      <anchorfile>namespacescran__blocks.html</anchorfile>
      <anchor>a6fcb43b96a8b97c00cfaf3ae83df028d</anchor>
      <arglist>(size_t n, std::vector&lt; Stat_ * &gt; in, Output_ *out, bool skip_nan)</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; Output_ &gt;</type>
      <name>average_vectors</name>
      <anchorfile>namespacescran__blocks.html</anchorfile>
      <anchor>ace4fcc523c305a36b9d4b7f031367d13</anchor>
      <arglist>(size_t n, std::vector&lt; Stat_ * &gt; in, bool skip_nan)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>average_vectors_weighted</name>
      <anchorfile>namespacescran__blocks.html</anchorfile>
      <anchor>a18cca7404ce3514a7d1f55a747c489be</anchor>
      <arglist>(size_t n, std::vector&lt; Stat_ * &gt; in, const Weight_ *w, Output_ *out, bool skip_nan)</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; Output_ &gt;</type>
      <name>average_vectors_weighted</name>
      <anchorfile>namespacescran__blocks.html</anchorfile>
      <anchor>a656535fcbb03d38ba16c66f941a5d1dd</anchor>
      <arglist>(size_t n, std::vector&lt; Stat_ * &gt; in, const Weight_ *w, bool skip_nan)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>compute_variable_weight</name>
      <anchorfile>namespacescran__blocks.html</anchorfile>
      <anchor>a0748c931e9c1250186a7794dcd440238</anchor>
      <arglist>(double s, const VariableWeightParameters &amp;params)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>compute_weights</name>
      <anchorfile>namespacescran__blocks.html</anchorfile>
      <anchor>a744e0293aa7028a351a0aad0c9c3662d</anchor>
      <arglist>(size_t num_blocks, const Size_ *sizes, WeightPolicy policy, const VariableWeightParameters &amp;variable, Weight_ *weights)</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; Weight_ &gt;</type>
      <name>compute_weights</name>
      <anchorfile>namespacescran__blocks.html</anchorfile>
      <anchor>a8a87f8dd41754b80ec0509f20ac2340f</anchor>
      <arglist>(const std::vector&lt; Size_ &gt; &amp;sizes, WeightPolicy policy, const VariableWeightParameters &amp;variable)</arglist>
    </member>
  </compound>
  <compound kind="page">
    <name>index</name>
    <title>Blocking utilities for scran</title>
    <filename>index.html</filename>
    <docanchor file="index.html" title="Blocking utilities for scran">md__2github_2workspace_2README</docanchor>
  </compound>
</tagfile>
