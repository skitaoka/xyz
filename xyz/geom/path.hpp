#ifndef XYZ_GEOM_PATH_HPP_
#define XYZ_GEOM_PATH_HPP_

#include "../core/config.hpp"
#include "../core/imagefilm.hpp"
#include "../geom/triangle.hpp"
#include "../geom/pathvertex.hpp"

namespace xyz {
class Path {
 public:
  static std::size_t const INVALID_CONSTRIBUTION = ~0U;

  explicit Path(__in std::size_t const maxPathLength);
  explicit Path(__in Path const &);

  Path &operator=(__in Path const &rhs);

  void swap(__inout Path &rhs);

  inline std::size_t GetMaxPathLength() const { return maxPathLength_; }

  void Begin(__in enum EMutationType);
  void End();
  void SetFilmPosition(__in std::size_t const &p);

  void Values(__out std::vector<pixel_descriptor_t> *const pValues) const;
  void ValuesAndSpecial(__out std::vector<pixel_descriptor_t> *const pValues,
                        __out pixel_descriptor_t *const pSpecial) const;

  float_t PDFSimplifiedMLT() const;
  float_t PDFFullMLT() const;
  void PDFsFullRELT(__out float4_t *const pPDFs) const;

  /// 粒子追跡法による寄与(C_{s,1})を蓄積する.
  void AccumulateS1(__in std::size_t const &p,  ///< [in] 画素の位置
                    __in std::size_t const &k,  ///< [in] 経路長-1
                    __in float3_t const &cs1);  ///< [in]

  /// 直接照明計算を行った場合の寄与(C_{1,t})を蓄積する.
  void Accumulate1T(__in float3_t const &c1t);

  /// 双方向経路追跡を行った場合の寄与(C_{s,t})を蓄積する.
  void AccumulateST(__in float3_t const &cst);

  /// 直接光源が見えている場合の寄与(C_{0,t})を蓄積する.
  void Accumulate0T(__in float3_t const &c0t, __in bool const &bSpecial);

 public:
#ifndef CONFIG_PINHOLE_CAMERA_MODEL
  float2_t vLensCoordinate;
#endif CONFIG_PINHOLE_CAMERA_MODEL

  std::vector<PathVertex> LightPathVertices;  ///< 光源経路頂点
  std::vector<PathVertex> EyePathVertices;    ///< 視点経路頂点

 private:
  std::size_t maxPathLength_;

  std::vector<pixel_descriptor_t> contributions_;  ///< 各経路長の経路からの寄与

  float3_t contribution_from_particle_path_;  ///< S1
  float3_t contribution_from_indirect_path_;  ///< ST
  float3_t contribution_from_explicit_path_;  ///< 1T
  float3_t contribution_from_implicit_path_;  ///< 0T
  float3_t contribution_from_specific_path_;  ///< 0T (special)
};

}  // end of namespace xyz

namespace std {
template <>
inline void swap(xyz::Path &a, xyz::Path &b) {
  a.swap(b);
}
}

#endif XYZ_GEOM_PATH_HPP_
