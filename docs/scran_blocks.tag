<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile doxygen_version="1.12.0">
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
    <includes id="block__weights_8hpp" name="block_weights.hpp" local="yes" import="no" module="no" objc="no">block_weights.hpp</includes>
    <includes id="average__vectors_8hpp" name="average_vectors.hpp" local="yes" import="no" module="no" objc="no">average_vectors.hpp</includes>
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
      <anchor>ad102233b847d4004e03035c29f243130</anchor>
      <arglist>(const std::size_t n, std::vector&lt; Stat_ * &gt; in, Output_ *const out, const bool skip_nan)</arglist>
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
      <anchor>afa41c174fefddebe4fc45c593f4edd2e</anchor>
      <arglist>(const std::size_t n, std::vector&lt; Stat_ * &gt; in, const Weight_ *const w, Output_ *const out, const bool skip_nan)</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; Output_ &gt;</type>
      <name>average_vectors_weighted</name>
      <anchorfile>namespacescran__blocks.html</anchorfile>
      <anchor>ac681cdd5f36d39f2e26f7a155551d259</anchor>
      <arglist>(const std::size_t n, std::vector&lt; Stat_ * &gt; in, const Weight_ *const w, const bool skip_nan)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>compute_variable_weight</name>
      <anchorfile>namespacescran__blocks.html</anchorfile>
      <anchor>a33ebed1decbfe3627ce4ddf0b99df825</anchor>
      <arglist>(const double s, const VariableWeightParameters &amp;params)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>compute_weights</name>
      <anchorfile>namespacescran__blocks.html</anchorfile>
      <anchor>a2eb0ccb73289d97436afd94824ec0fae</anchor>
      <arglist>(const std::size_t num_blocks, const Size_ *const sizes, const WeightPolicy policy, const VariableWeightParameters &amp;variable, Weight_ *const weights)</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; Weight_ &gt;</type>
      <name>compute_weights</name>
      <anchorfile>namespacescran__blocks.html</anchorfile>
      <anchor>a182b74f7588264fae43fa06015f045c7</anchor>
      <arglist>(const std::vector&lt; Size_ &gt; &amp;sizes, const WeightPolicy policy, const VariableWeightParameters &amp;variable)</arglist>
    </member>
  </compound>
  <compound kind="page">
    <name>index</name>
    <title>Blocking utilities for libscran</title>
    <filename>index.html</filename>
    <docanchor file="index.html" title="Blocking utilities for libscran">md__2github_2workspace_2README</docanchor>
  </compound>
</tagfile>
