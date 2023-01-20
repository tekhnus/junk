(use-modules
 (guix packages)
 (guix git-download)
 (guix build-system cmake)
 (guix licenses)
 (gnu packages rpc)
 (gnu packages linux)
 (gnu packages version-control)
 (gnu packages gl)
 (gnu packages flex)
 (gnu packages bison)
 (gnu packages boost)
 (gnu packages commencement)
 (gnu packages game-development)
 (gnu packages libevent))

(define apache-thrift-with-libevent
  (package
   (inherit apache-thrift)
   (inputs (modify-inputs (package-inputs apache-thrift)
                          (append libevent)
                          (delete boost)
                          (append boost-static)))
   (arguments
    '(#:tests?
      #f
      #:configure-flags
      (list
       (string-append "--with-boost="
                      (assoc-ref %build-inputs "boost-static"))
       (string-append "--with-libevent="
                      (assoc-ref %build-inputs "libevent")))))))

(define sfgui
  (package
   (name "sfgui")
   (version "")
   (source (origin
            (method git-fetch)
            (uri (git-reference
                  (url "https://github.com/TankOs/SFGUI/")
                  (commit "83471599284b2a23027b9ab4514684a6eeb08a19")))
            (file-name (git-file-name name version))
            (sha256
             (base32
              "0x4c79hjgzm8hxkchi5zxlc1fi5jikxddmlzb6bpyym4rjrvhm6z"))))
   (build-system cmake-build-system)
   (arguments
    `(#:tests? #false))
   (outputs '("out" "debug"))
   (inputs
    (list sfml mesa glew))
   (synopsis "")
   (description "")
   (license zlib)
   (home-page "")))

(packages->manifest
  (list flex
        bison
        boost
        sfml
        sfgui
        box2d
        git
        libevent
        apache-thrift-with-libevent
        gcc-toolchain
        mesa
        glew
        linux-libre-headers
        (list apache-thrift-with-libevent "lib")))
