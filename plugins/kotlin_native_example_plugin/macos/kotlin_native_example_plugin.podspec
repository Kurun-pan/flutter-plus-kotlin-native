#
# To learn more about a Podspec see http://guides.cocoapods.org/syntax/podspec.html
#
Pod::Spec.new do |s|
  s.name             = 'kotlin_native_example_plugin'
  s.version          = '0.0.3'
  s.summary          = 'A new flutter plugin project.'
  s.description      = <<-DESC
A new flutter plugin project.
                       DESC
  s.homepage         = 'http://example.com'
  s.license          = { :file => '../LICENSE' }
  s.author           = { 'Your Company' => 'email@example.com' }
  s.source           = { :path => '.' }
  s.source_files     = 'Classes/**/*'
  s.dependency 'FlutterMacOS'

  s.platform = :osx
  s.osx.deployment_target = '10.11'

  s.preserve_paths = 'KotlinNative.framework'
  s.xcconfig = { 'OTHER_LDFLAGS' => '-framework KotlinNative' }
  s.vendored_frameworks = 'KotlinNative.framework'
  s.public_header_files = "KotlinNative.framework/Headers/*.h"
  #s.resource_bundle = { 'KotlinNative-Resources' => './*' }
end
