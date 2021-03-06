<!-- This Source Code Form is licensed MPL-2.0: http://mozilla.org/MPL/2.0 -->

<docs>
  # B-ICON
  This element displays icons from various icon fonts.
  Note, to style the color of icon font symbols, simply apply the `color` CSS property to this element
  (styling `fill` as for SVG elements is not needed).
  ## Props:
  *iconclass*
  : A CSS class to apply to this icon.
  *fa*
  : The name of a "Fork Awesome" icon (compatible with "Font Awesome 4"), see the [Fork Awesome Icons](https://forkaweso.me/Fork-Awesome/cheatsheet/).
  *mi*
  : The name of a "Material Icons" icon, see the [Material Design Icons](https://material.io/tools/icons/).
  *uc*
  : A unicode character literal, see the [Unicode symbols block list](https://en.wikipedia.org/wiki/Unicode_symbols#Symbol_block_list).
  *ic*
  : A prefixed variant of `fa`, `mi`, `uc`.
  *nosize*
  : Prevent the element from applying default size constraints.
  *fw*
  : Apply fixed-width sizing.
  *lg*
  : Make the icon 33% larger than its container.
</docs>

<style lang="scss">
  @import 'mixins.scss';
  .b-icon {
    margin: 0; padding: 0; text-align: center;
    &.b-icon-dfl { height: 1em; width: 1em; }
    &.b-icon-fw	 { height: 1em; width: 1.28571429em; text-align: center; }
    &.b-icon-lg	 { font-size: 1.33333333em; }
    &.material-icons.b-icon-dfl { font-size: 1em; }
  }
</style>

<template>
  <span    v-if="uc_" class="b-icon" :class="iconclasses" role="icon" aria-hidden="true">{{ uc_ }}</span>
  <i  v-else-if="fa_" class="b-icon" :class="iconclasses" role="icon" aria-hidden="true"></i>
  <i  v-else-if="mi_" class="b-icon" :class="iconclasses" role="icon" aria-hidden="true">{{ mi_ }}</i>
  <span v-else-if="1" class="b-icon" :class="iconclasses" role="icon" aria-hidden="true"><slot /></span>
</template>
<!-- SVG-1.1 notation: <use xmlns:xlink="http://www.w3.org/1999/xlink" xlink:href="...svg"></use> -->

<script>
const STR = { type: String, default: '' }; // empty string default
export default {
  name: 'b-icon',
  props: { iconclass: STR, ic: STR, fa: STR, mi: STR, uc: STR,
	   'nosize': undefined, 'fw': undefined, 'lg': undefined },
  computed: {
    mi_() { return this.ic.startsWith ('mi-') ? this.ic.substr (3) : this.mi; },
    uc_() { return this.ic.startsWith ('uc-') ? this.ic.substr (3) : this.uc; },
    fa_() { return this.ic.startsWith ('fa-') ? this.ic.substr (3) : this.fa; },
    iconclasses() {
      let classes = (this.iconclass || '').split (/ +/);
      if (this.fw || this.fw === '')
	classes.push ('b-icon-fw');
      else if (!(this.nosize || this.nosize == ''))
	classes.push ('b-icon-dfl');
      if (this.lg || this.lg == '')
	classes.push ('b-icon-lg');
      if (this.mi_)
	classes.push ('material-icons');
      if (this.fa_)
	{
	  classes.push ('fa');
	  classes.push ('fa-' + this.fa_);
	}
      return classes.join (' ');
    },
  },
  methods: {
    emit (what, ev) {
      this.$emit (what, ev);
    },
  },
};
</script>
