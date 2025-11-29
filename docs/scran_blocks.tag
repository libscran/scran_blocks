<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile doxygen_version="1.12.0">
  <compound kind="file">
    <name>block_weights.hpp</name>
    <path>scran_blocks/</path>
    <filename>block__weights_8hpp.html</filename>
    <class kind="struct">scran_blocks::VariableWeightParameters</class>
    <namespace>scran_blocks</namespace>
  </compound>
  <compound kind="file">
    <name>parallel_means.hpp</name>
    <path>scran_blocks/</path>
    <filename>parallel__means_8hpp.html</filename>
    <namespace>scran_blocks</namespace>
  </compound>
  <compound kind="file">
    <name>parallel_quantiles.hpp</name>
    <path>scran_blocks/</path>
    <filename>parallel__quantiles_8hpp.html</filename>
    <class kind="class">scran_blocks::SingleQuantile</class>
    <namespace>scran_blocks</namespace>
  </compound>
  <compound kind="file">
    <name>scran_blocks.hpp</name>
    <path>scran_blocks/</path>
    <filename>scran__blocks_8hpp.html</filename>
    <includes id="block__weights_8hpp" name="block_weights.hpp" local="yes" import="no" module="no" objc="no">block_weights.hpp</includes>
    <includes id="parallel__means_8hpp" name="parallel_means.hpp" local="yes" import="no" module="no" objc="no">parallel_means.hpp</includes>
    <includes id="parallel__quantiles_8hpp" name="parallel_quantiles.hpp" local="yes" import="no" module="no" objc="no">parallel_quantiles.hpp</includes>
    <namespace>scran_blocks</namespace>
  </compound>
  <compound kind="class">
    <name>scran_blocks::SingleQuantile</name>
    <filename>classscran__blocks_1_1SingleQuantile.html</filename>
    <templarg>typename Output_</templarg>
    <templarg>typename Size_</templarg>
    <member kind="function">
      <type></type>
      <name>SingleQuantile</name>
      <anchorfile>classscran__blocks_1_1SingleQuantile.html</anchorfile>
      <anchor>a86b96118f4d7449d12d7b2899930c44e</anchor>
      <arglist>(Size_ n, double quantile)</arglist>
    </member>
    <member kind="function">
      <type>Output_</type>
      <name>operator()</name>
      <anchorfile>classscran__blocks_1_1SingleQuantile.html</anchorfile>
      <anchor>a396014f8cc146189c25cceba041791f5</anchor>
      <arglist>(Iterator_ begin, Iterator_ end) const</arglist>
    </member>
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
    <class kind="class">scran_blocks::SingleQuantile</class>
    <class kind="struct">scran_blocks::VariableWeightParameters</class>
    <member kind="enumeration">
      <type></type>
      <name>WeightPolicy</name>
      <anchorfile>namespacescran__blocks.html</anchorfile>
      <anchor>ac2412948da94055ff438267ba089ba97</anchor>
      <arglist></arglist>
      <enumvalue file="namespacescran__blocks.html" anchor="ac2412948da94055ff438267ba089ba97ab50339a10e1de285ac99d4c3990b8693">NONE</enumvalue>
      <enumvalue file="namespacescran__blocks.html" anchor="ac2412948da94055ff438267ba089ba97a62e5cef85d46f1a5a2144d9fd463b79e">SIZE</enumvalue>
      <enumvalue file="namespacescran__blocks.html" anchor="ac2412948da94055ff438267ba089ba97ae61ad9b2553a293b4a3f4d3b4fa5ab31">VARIABLE</enumvalue>
      <enumvalue file="namespacescran__blocks.html" anchor="ac2412948da94055ff438267ba089ba97a969f331a87d8c958473c32b4d0e61a44">EQUAL</enumvalue>
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
    <member kind="function">
      <type>void</type>
      <name>parallel_means</name>
      <anchorfile>namespacescran__blocks.html</anchorfile>
      <anchor>ad47cb191dd54e5b23cde2ef295b06046</anchor>
      <arglist>(const std::size_t n, std::vector&lt; Stat_ * &gt; in, Output_ *const out, const bool skip_nan)</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; Output_ &gt;</type>
      <name>parallel_means</name>
      <anchorfile>namespacescran__blocks.html</anchorfile>
      <anchor>ab4231fa5b1c8fa34ab298fa0c13ba0bf</anchor>
      <arglist>(const std::size_t n, std::vector&lt; Stat_ * &gt; in, const bool skip_nan)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>parallel_weighted_means</name>
      <anchorfile>namespacescran__blocks.html</anchorfile>
      <anchor>abac57f9512b34b4e22871c62fca4020e</anchor>
      <arglist>(const std::size_t n, std::vector&lt; Stat_ * &gt; in, const Weight_ *const w, Output_ *const out, const bool skip_nan)</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; Output_ &gt;</type>
      <name>parallel_weighted_means</name>
      <anchorfile>namespacescran__blocks.html</anchorfile>
      <anchor>a55275bde36deccc819c42713e3ec81bd</anchor>
      <arglist>(const std::size_t n, std::vector&lt; Stat_ * &gt; in, const Weight_ *const w, const bool skip_nan)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>parallel_quantiles</name>
      <anchorfile>namespacescran__blocks.html</anchorfile>
      <anchor>abef134052291ee3f5bce4011f41c5381</anchor>
      <arglist>(const std::size_t n, const std::vector&lt; Stat_ * &gt; &amp;in, const double quantile, Output_ *const out, const bool skip_nan)</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; Output_ &gt;</type>
      <name>parallel_quantiles</name>
      <anchorfile>namespacescran__blocks.html</anchorfile>
      <anchor>a2e8bd1c6e5ea1cd9c875b2dbe7e986f8</anchor>
      <arglist>(const std::size_t n, const std::vector&lt; Stat_ * &gt; &amp;in, const double quantile, const bool skip_nan)</arglist>
    </member>
  </compound>
  <compound kind="page">
    <name>index</name>
    <title>Blocking utilities for libscran</title>
    <filename>index.html</filename>
    <docanchor file="index.html" title="Blocking utilities for libscran">md__2github_2workspace_2README</docanchor>
  </compound>
</tagfile>
